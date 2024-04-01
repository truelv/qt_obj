#ifndef RMOTECAMERA_H
#define RMOTECAMERA_H

#include <QWidget>

namespace Ui {
class RmoteCamera;
}

class RmoteCamera : public QWidget
{
    Q_OBJECT

public:
    explicit RmoteCamera(QWidget *parent = 0);
    ~RmoteCamera();

private:
    Ui::RmoteCamera *ui;
};

#endif // RMOTECAMERA_H
