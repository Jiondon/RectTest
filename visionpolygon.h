#ifndef VISIONPOLYGON_H
#define VISIONPOLYGON_H

#include <QObject>
#include "visionitem.h"

class VisionPolygon : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPolygon(VisionItem *parent = 0);

signals:

public slots:
};

#endif // VISIONPOLYGON_H
