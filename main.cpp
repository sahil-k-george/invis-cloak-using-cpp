#include <QApplication>
#include <QCamera>
#include<QMediaCaptureSession>
#include<QVideoSink>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QWidget>
#include<QImageCapture>
#include<QPushButton>
#include<QImageCapture>
#include<QSlider>
#include<QDebug>
#include<QGroupBox>
#include<QFormLayout>
#include<QMediaCaptureSession>
#include<QtConcurrent>
#include<QFuture>
#include<QMediaDevices>
#include<QCameraDevice>
#include<QCameraFormat>
#include<QElapsedTimer>


QElapsedTimer frameTimer;
std::atomic<bool>
    processingFrame(false);

//#include<QVideoFrame>
//#include<QMediaDevices>

// Creating the color keying function

QImage applyChromaKey(const QImage &frame, const QImage &background, QColor keyColor, int tolerance){
    QImage result = frame.convertToFormat(QImage::Format_ARGB32);
    QImage bg = background.scaled(frame.size());

    for (int y = 0; y < result.height(); ++y){
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        QRgb *bgLine = reinterpret_cast<QRgb*>(bg.scanLine(y));
        for (int x = 0; x < result.width(); ++x){
            QColor pixelColor(line[x]);
            int dr = abs(pixelColor.red() - keyColor.red());
            int dg = abs(pixelColor.green() - keyColor.green());
            int db = abs(pixelColor.blue() - keyColor.blue());
            if (dr + dg + db < tolerance){
                line[x] = bgLine[x]; //Replace Pixel
            }
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Creating Main Window
    QWidget window;
    window.setWindowTitle("CAMERA DIRECT OUTPUT");

    // creating the UI
    QLabel *videoLabel = new QLabel;
    videoLabel->setMinimumSize(640, 480);
    QPushButton *captureButton = new QPushButton("Capture Image");

    // Creating the sliders for tolerance
    QSlider *tolerance = new QSlider(Qt::Horizontal);
    tolerance->setRange(0, 255*3); // setting range of the slider
    tolerance->setValue(80); // setting default startup value

    // Creating slider for selector -red
    QSlider *rSlider = new QSlider(Qt::Horizontal);
    rSlider->setRange(0, 255); // setting range of the slider
    rSlider->setValue(0); // setting default startup value

    // Creating slider for selector -green
    QSlider *gSlider = new QSlider(Qt::Horizontal);
    gSlider->setRange(0, 255); // setting range of the slider
    gSlider->setValue(255); // setting default startup value

    // Creating slider for selector -blue
    QSlider *bSlider = new QSlider(Qt::Horizontal);
    bSlider->setRange(0, 255); // setting range of the slider
    bSlider->setValue(0); // setting default startup value

    // Displaying the video widget or creating a session
    //QVideoWidget *videoWidget = new QVideoWidget;
    QGroupBox *controlsBox = new QGroupBox("COLOR CONTROLS");
    QFormLayout *controlsLayout = new QFormLayout;

    controlsLayout->addRow("Tolerance", tolerance);
    controlsLayout->addRow("Red", rSlider);
    controlsLayout->addRow("Green", gSlider);
    controlsLayout->addRow("Blue", bSlider);

    controlsBox->setLayout(controlsLayout);


    // creating the capturing session
    // QMediaCaptureSession *captureSession = new QMediaCaptureSession;

    // setting up the camera
    QCamera *camera = new QCamera;
    // camera->setCameraFormat(QCameraFormat(320, 240, 10.0, QVideoFrameFormat::Format_ABGR8888));  // forcing cam to run at 320x240 @ 10fps
    QCameraDevice device = QMediaDevices::defaultVideoInput();
    camera->setCameraDevice(device);

    const QList<QCameraFormat> formats = device.videoFormats();
    QCameraFormat chosenFormat;
    for(const QCameraFormat &format : formats){
        if (format.resolution().width() <= 640 && //320 works.....(for me)
            format.resolution().height() <= 480 && //240 works.....(for me)
            format.minFrameRate() <= 30)    //cam supports only 30fps.....(for me)
        {
            chosenFormat = format;
            camera->setCameraFormat(chosenFormat);
            break;
        }
    }
    //if (chosenFormat.isAvailable){
    //camera->setCameraFormat(chosenFormat);
    //}
    // Capturing the image:
    QImageCapture *capturedimage = new QImageCapture;
    QVideoSink *videoSink = new QVideoSink;
    QMediaCaptureSession *captureSession = new QMediaCaptureSession;
    captureSession->setCamera(camera);

    captureSession->setImageCapture(capturedimage);
    captureSession->setVideoSink(videoSink);

    camera->start();
    frameTimer.start(); //for frame limiting
    // storing thr captured image
    QImage lastCaptured;
    QObject::connect(capturedimage, &QImageCapture::imageCaptured, [&](int id, const QImage &preview)
                     {lastCaptured = preview.scaled(320, 240, Qt::KeepAspectRatio);
                        qDebug() << "ID:" << id;});

    // processing live frames with the keying function
    QObject::connect(videoSink, &QVideoSink::videoFrameChanged, [&](const QVideoFrame &frame)
                     {
                         if (!frame.isValid()) return;
                         QImage input = frame.toImage();
                         if (input.isNull()) return;
                         // Frame Limiter here V
                        // if (frameTimer.elapsed() < 0) {  // change the value here for diffrerent framerates
                          //   return;
                         //}
                         frameTimer.restart();
                         QImage output;
                         if (!lastCaptured.isNull()) {
                             if (processingFrame.exchange(true)) {
                                 return;
                             }
                             QColor keyColor(rSlider->value(), gSlider->value(), bSlider->value());
                             int tolval = tolerance->value();
                             // threading it to different threads
                             QtConcurrent::run([=](){
                                 QImage output = applyChromaKey(input, lastCaptured, keyColor,tolval);
                                 QMetaObject::invokeMethod(videoLabel, [=]() {
                                     videoLabel->setPixmap(QPixmap::fromImage(output));
                                 }, Qt::QueuedConnection);
                                 processingFrame = false;
                             });


                         } else {
                             output = input; // show live feed until bg capture
                         }
                         videoLabel->setPixmap(QPixmap::fromImage(output));
                     });


    // Addimg capture functionality to the session
    // captureSession->setImageCapture(capturedimage);

    // connecting everything together

    // Linking capture sesion to camrea and vid out

    // captureSession->setVideoOutput(videoWidget);

    // Adding the capture button
    //QPushButton *background = new QPushButton("Set Background");


    QLabel *status = new QLabel("NO BACKGROUND ADDED");

    QObject::connect(captureButton, &QPushButton::clicked, [&](){
        if (camera->isActive())
            capturedimage->capture();

    });

    QObject::connect(capturedimage, &QImageCapture::imageCaptured, [&](int id, const QImage &preview){
        lastCaptured = preview;
        status->setText("BACKGROUND READY: ID: " + QString::number(id));

    });

    // adding the switch to invis cloak button
    //QPushButton *liveview = new QPushButton("Live View");

    //QObject::connect(liveview, &QPushButton::clicked, [&](){
    //    if (camera->isAvailable())
    //        camera->start();
    //});
    // starting the camera



    //Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoLabel);
    layout->addWidget(captureButton);
    layout->addWidget(status);
    layout->addWidget(controlsBox);

    window.setLayout(layout);

    window.resize(700, 650);
    window.show();

    return app.exec();


}
