/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     JiangChangli
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CPICTUREITEM_H
#define CPICTUREITEM_H

#include <QGraphicsPixmapItem>
#include "cgraphicsrectitem.h"

class CPictureItem : public CGraphicsRectItem
{
public:
    enum EFilpDirect {EFilpHor, EFilpVer};

    explicit CPictureItem(const QPixmap &pixmap = QPixmap(), CGraphicsItem *parent = nullptr, const QByteArray &fileSrcData = QByteArray());
    explicit CPictureItem(const QRectF &rect, const QPixmap &pixmap, CGraphicsItem *parent = nullptr, const QByteArray &fileSrcData = QByteArray());
    ~CPictureItem() override;

    /**
     * @brief type 图元的类型(图片)
     */
    int  type() const override;

    void setRotation90(bool leftOrRight);

    /**
     * @brief doFilp 在当前基础上翻转一下
     * @return
     */
    void doFilp(EFilpDirect dir = EFilpHor);

    /**
     * @brief setFilpBaseOrg 设置在初始图像上是否翻转,否则和原图一致
     */
    void setFilpBaseOrg(EFilpDirect dir, bool b);

    /**
     * @brief isFilped 图像是否翻转过(相对原图)
     */
    bool isFilped(EFilpDirect dir);

    /**
     * @brief 加载图元的信息
     */
    void loadGraphicsUnit(const CGraphicsUnit &data) override;

    /**
     * @brief 获取图元的信息
     */
    CGraphicsUnit getGraphicsUnit(EDataReason reson) const override;

    /**
     * @brief 设置图片
     */
    void setPixmap(const QPixmap &pixmap);

    /**
     * @brief 设置旋转角度
     */
    void setAngle(const qreal &angle);

    /**
     * @brief isPosPenetrable 某一位置在图元上是否是可穿透的（透明的）
     * @param posLocal 该图元坐标系的坐标位置
     */
    bool isPosPenetrable(const QPointF &posLocal) override;

    /**
     * @brief isPosPenetrable 某一矩形区域在图元上是否是可穿透的（透明的）
     * @param rectLocal 该图元坐标系的某一矩形区域
     */
    bool isRectPenetrable(const QRectF &rectLocal) override;

    /**
     * @brief getSelfOrgShape 获取到自身的原始形状
     */
    QPainterPath getSelfOrgShape() const override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPixmap m_pixmap;
    qreal   m_angle;
    QByteArray _srcByteArry;

    bool flipHorizontal; // 水平翻转
    bool flipVertical;   // 垂直翻转
};

#endif // CPICTUREITEM_H
