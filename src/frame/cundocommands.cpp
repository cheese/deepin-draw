/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     WangXin
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
#include "cundocommands.h"

#include "globaldefine.h"
#include "cgraphicslineitem.h"
#include "cgraphicsrectitem.h"
#include "cgraphicspolygonitem.h"
#include "cgraphicspolygonalstaritem.h"
#include "cgraphicspenitem.h"
#include "cdrawparamsigleton.h"
#include "cdrawscene.h"
#include "cgraphicslineitem.h"
#include "cgraphicsmasicoitem.h"
#include "cgraphicsitemselectedmgr.h"
#include "cgraphicstextitem.h"
//#include "cgraphicsitemhighlight.h"
#include "cpictureitem.h"

#include "frame/cviewmanagement.h"
#include "frame/cgraphicsview.h"
#include "cgraphicsitemselectedmgr.h"

#include "service/cmanagerattributeservice.h"

#include "widgets/ctextedit.h"

#include <QUndoCommand>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QBrush>
#include <QDebug>

//升序排列用
static bool zValueSortASC(QGraphicsItem *info1, QGraphicsItem *info2)
{
    return info1->zValue() <= info2->zValue();
}
//降序排列用
static bool zValueSortDES(QGraphicsItem *info1, QGraphicsItem *info2)
{
    return info1->zValue() >= info2->zValue();
}

//CRotateShapeCommand::CRotateShapeCommand(CDrawScene *scene, QGraphicsItem *item, const qreal oldAngle, QUndoCommand *parent)
//    : QUndoCommand(parent)
//    , myOldAngle(oldAngle)
//    , newAngle(item->rotation())
//{
//    myGraphicsScene = scene;
//    myItem = item;
//}

//void CRotateShapeCommand::undo()
//{
//    myItem->setRotation(myOldAngle);
//    myGraphicsScene->clearSelection();
//    myItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myItem->scene()->update();
//    myGraphicsScene->setModify(true);
//}

//void CRotateShapeCommand::redo()
//{
//    myItem->setRotation(newAngle);
//    myGraphicsScene->clearSelection();
//    myItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myItem->update();
//    myGraphicsScene->setModify(true);
//}

//CSetPropertyCommand::CSetPropertyCommand(CDrawScene *scene, CGraphicsItem *item, QPen pen, QBrush brush, bool bPenChange, bool bBrushChange, QUndoCommand *parent)
//    : QUndoCommand(parent)
//    , m_pItem(item)
//    , m_oldPen(item->pen())
//    , m_newPen(pen)
//    , m_newBrush(brush)
//    , m_bPenChange(bPenChange)
//    , m_bBrushChange(bBrushChange)
//{
//    myGraphicsScene = scene;
//    m_oldBrush = item->brush();
//}

//CSetPropertyCommand::~CSetPropertyCommand()
//{
//}

//void CSetPropertyCommand::undo()
//{
//    if (m_bPenChange) {
//        m_pItem->setPen(m_oldPen);
//        CGraphicsItem *pItem = dynamic_cast<CGraphicsItem *>(m_pItem);
//        if (pItem != nullptr) {
//            pItem->updateShape();
//        }
//    }

//    if (m_bBrushChange) {
//        m_pItem->setBrush(m_oldBrush);
//    }

//    // 此处还需要对文字进行进一步撤销处理才可以
//    CGraphicsTextItem *textItem = dynamic_cast<CGraphicsTextItem *>(m_pItem);
//    if (textItem == nullptr || !textItem->isEditable()) {
//        myGraphicsScene->clearSelection();
//        m_pItem->setSelected(true);
//    }
//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//void CSetPropertyCommand::redo()
//{
//    if (m_bPenChange) {
//        m_pItem->setPen(m_newPen);
//        CGraphicsItem *pItem = dynamic_cast<CGraphicsItem *>(m_pItem);
//        if (pItem != nullptr) {
//            pItem->updateShape();
//        }
//    }

//    if (m_bBrushChange) {
//        m_pItem->setBrush(m_newBrush);
//    }

//    CGraphicsTextItem *textItem = dynamic_cast<CGraphicsTextItem *>(m_pItem);

//    if (textItem == nullptr || !textItem->isEditable()) {
//        myGraphicsScene->clearSelection();
//        m_pItem->setSelected(true);
//    }

//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//CSetRectXRediusCommand::CSetRectXRediusCommand(CDrawScene *scene, CGraphicsRectItem *item, int redius, bool bRediusChange, QUndoCommand *parent)
//    : QUndoCommand(parent)
//    , myGraphicsScene(scene)
//    , m_pItem(item)
//    , m_newRectXRedius(redius)
//    , m_bRectXRediusChange(bRediusChange)
//{
//    m_oldRectXRedius = item->getXRedius();
//}

//CSetRectXRediusCommand::~CSetRectXRediusCommand()
//{
//}

//void CSetRectXRediusCommand::undo()
//{
//    if (m_bRectXRediusChange) {
//        m_pItem->setXYRedius(m_oldRectXRedius, m_oldRectXRedius);
//        myGraphicsScene->clearSelection();
//        m_pItem->setSelected(true);
//    }
//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//void CSetRectXRediusCommand::redo()
//{
//    if (m_bRectXRediusChange) {
//        m_pItem->setXYRedius(m_newRectXRedius, m_newRectXRedius);
//        m_pItem->update();
//        myGraphicsScene->clearSelection();
//        m_pItem->setSelected(true);
//    }

//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//CSetPolygonAttributeCommand::CSetPolygonAttributeCommand(CDrawScene *scene, CGraphicsPolygonItem *item, int newNum)
//    : m_pItem(item)
//    , m_nNewNum(newNum)
//{
//    myGraphicsScene = scene;
//    m_nOldNum = m_pItem->nPointsCount();
//}

//void CSetPolygonAttributeCommand::undo()
//{
//    m_pItem->setPointCount(m_nOldNum);
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->setModify(true);
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//void CSetPolygonAttributeCommand::redo()
//{
//    m_pItem->setPointCount(m_nNewNum);
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->setModify(true);
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//CSetPolygonStarAttributeCommand::CSetPolygonStarAttributeCommand(CDrawScene *scene, CGraphicsPolygonalStarItem *item, int newNum, int newRadius)
//    : m_pItem(item)
//    , m_nNewNum(newNum)
//    , m_nNewRadius(newRadius)
//{
//    myGraphicsScene = scene;
//    m_nOldNum = m_pItem->anchorNum();
//    m_nOldRadius = m_pItem->innerRadius();
//}

//void CSetPolygonStarAttributeCommand::undo()
//{
//    myGraphicsScene->getItemsMgr()->clear();
//    m_pItem->updatePolygonalStar(m_nOldNum, m_nOldRadius);
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();

//    myGraphicsScene->setModify(true);
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//void CSetPolygonStarAttributeCommand::redo()
//{
//    myGraphicsScene->getItemsMgr()->clear();
//    m_pItem->updatePolygonalStar(m_nNewNum, m_nNewRadius);
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();

//    myGraphicsScene->setModify(true);
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//CSetPenAttributeCommand::CSetPenAttributeCommand(CDrawScene *scene, CGraphicsPenItem *item, bool isStart, ELineType type)
//    : m_pItem(item)
//    , m_newStartType(noneLine)
//    , m_newEndType(noneLine)
//{
//    myGraphicsScene = scene;

//    if (isStart) {
//        m_newStartType = type;
//    } else {
//        m_newEndType = type;
//    }

//    m_oldStartType = item->getPenStartType();
//    m_oldEndType = item->getPenEndType();
//}

//void CSetPenAttributeCommand::undo()
//{
//    m_pItem->setPenStartType(static_cast<ELineType>(m_oldStartType));
//    m_pItem->setPenEndType(static_cast<ELineType>(m_oldEndType));

//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//void CSetPenAttributeCommand::redo()
//{
//    m_pItem->setPenStartType(static_cast<ELineType>(m_oldStartType));
//    m_pItem->setPenEndType(static_cast<ELineType>(m_oldEndType));

//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//CSetLineAttributeCommand::CSetLineAttributeCommand(CDrawScene *scene, CGraphicsLineItem *item, bool isStart, ELineType type)
//    : m_pItem(item)
//    , m_newStartType(noneLine)
//    , m_newEndType(noneLine)
//{
//    myGraphicsScene = scene;
//    m_isStart = isStart;

//    if (isStart) {
//        m_newStartType = type;
//        m_oldStartType = item->getLineStartType();
//    } else {
//        m_newEndType = type;
//        m_oldEndType = item->getLineEndType();
//    }
//}

//void CSetLineAttributeCommand::undo()
//{
//    if (m_isStart) {
//        m_pItem->setLineStartType(m_oldStartType);
//    } else {
//        m_pItem->setLineEndType(m_oldEndType);
//    }
//    m_pItem->calcVertexes();
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

//void CSetLineAttributeCommand::redo()
//{
//    if (m_isStart) {
//        m_pItem->setLineStartType(m_newStartType);
//    } else {
//        m_pItem->setLineEndType(m_newEndType);
//    }
//    m_pItem->calcVertexes();
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//    myGraphicsScene->updateBlurItem(m_pItem);
//}

COneLayerUpCommand::COneLayerUpCommand(CDrawScene *scene, const QList<QGraphicsItem *> &items, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    QList<QGraphicsItem *> curItems;
    for (auto item : scene->items(Qt::AscendingOrder)) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            if (curItems.isEmpty()) {
                if (items.contains(item)) {
                    curItems.append(item);
                }
            } else {
                if (items.contains(item)) {
                    curItems.append(item);
                } else {
                    m_items.append(qMakePair<QGraphicsItem *, QList<QGraphicsItem *>>(item, curItems));
                    curItems.clear();
                }
            }
        }
    }
    m_oldItemZValue.clear();
    m_selectItems = items;
    m_isUndoExcuteSuccess = true;
    m_isRedoExcuteSuccess = false;
}

void COneLayerUpCommand::undo()
{
    qDebug() << "COneLayerUpCommand undo";
    if (!m_isRedoExcuteSuccess) {
        return;
    }

    QList<QGraphicsItem *> itemList = myGraphicsScene->items();

    m_isRedoExcuteSuccess = false;

    int count = m_oldItemZValue.count();
    for (int i = 0; i < count; i++) {
        QGraphicsItem *item = m_oldItemZValue.keys().at(i);
        item->setZValue(m_oldItemZValue[item]);
        //myGraphicsScene->updateBlurItem(item);
        m_isRedoExcuteSuccess = true;
    }
    //重置保存的最大z值
    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            continue;
        }
        if (allItem->zValue() > myGraphicsScene->getMaxZValue()) {
            myGraphicsScene->setMaxZValue(allItem->zValue());
        }
    }

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (m_isRedoExcuteSuccess) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }
    myGraphicsScene->updateBlurItem();
}

void COneLayerUpCommand::redo()
{
    qDebug() << "COneLayerUpCommand redo";
    if (!m_isUndoExcuteSuccess) {
        return;
    }

    m_isRedoExcuteSuccess = false;
    //移除z值为0的和多选管理图元
    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        if (allItems.at(i)->zValue() == 0.0) {
            allItems.removeAt(i);
            continue;
        }
        if (allItems[i]->type() <= QGraphicsItem::UserType || allItems[i]->type() >= EGraphicUserType::MgrType) {
            allItems.removeAt(i);
            continue;
        }
    }
    //升序排列
    qSort(m_selectItems.begin(), m_selectItems.end(), zValueSortASC);
    for (int selectIndex = 0; selectIndex < m_selectItems.size(); selectIndex++) {
        QGraphicsItem *selectItem = m_selectItems.at(selectIndex);
        QGraphicsItem *selectItemNext = nullptr;
        if ((selectIndex + 1) < m_selectItems.size()) {
            selectItemNext = m_selectItems.at(selectIndex + 1);
        }
        m_isRedoExcuteSuccess = true;
        qSort(allItems.begin(), allItems.end(), zValueSortASC);
        for (int allItemIndex = 0; allItemIndex < allItems.size(); allItemIndex++) {
            QGraphicsItem *allItem = allItems.at(allItemIndex);
            if (allItem->zValue() > selectItem->zValue()) {
                if (allItem == selectItemNext) {
                    break;
                }
                //记录原来z值
                m_oldItemZValue[allItem] = allItem->zValue();
                m_oldItemZValue[selectItem] = selectItem->zValue();

                qreal tmpZValue = selectItem->zValue();
                selectItem->setZValue(allItem->zValue());
                allItem->setZValue(tmpZValue);
                break;
            }
        }
    }
    //重置保存的最大z值
    allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            continue;
        }
        if (allItem->zValue() > myGraphicsScene->getMaxZValue()) {
            myGraphicsScene->setMaxZValue(allItem->zValue());
        }
    }

    /* 刷新属性展示和多选的大小 */
    CGraphicsItemSelectedMgr *pMgr = CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr();
    pMgr->updateAttributes();
    pMgr->updateBoundingRect();

    /* 刷新鼠标和高亮 */
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (m_isRedoExcuteSuccess) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }
    myGraphicsScene->updateBlurItem();
}

COneLayerDownCommand::COneLayerDownCommand(CDrawScene *scene, const QList<QGraphicsItem *> &items, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    QList<QGraphicsItem *> curItems;
    QGraphicsItem *preItem = nullptr;
    for (auto item : scene->items(Qt::AscendingOrder)) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            if (items.contains(item)) {
                if (preItem != nullptr) {
                    curItems.append(item);
                }
            } else {
                if (!curItems.isEmpty()) {
                    m_items.append(qMakePair<QGraphicsItem *, QList<QGraphicsItem *>>(preItem, curItems));
                    curItems.clear();
                }
                preItem = item;
            }
        }
    }
    if (preItem != nullptr && !curItems.isEmpty()) {
        m_items.append(qMakePair<QGraphicsItem *, QList<QGraphicsItem *>>(preItem, curItems));
    }
    m_oldItemZValue.clear();
    m_selectItems = items;
    m_isUndoExcuteSuccess = true;
    m_isRedoExcuteSuccess = false;
}

COneLayerDownCommand::~COneLayerDownCommand()
{
}

void COneLayerDownCommand::undo()
{
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!downUndo";
    if (!m_isRedoExcuteSuccess) {
        return;
    }

    m_isRedoExcuteSuccess = false;

    int count = m_oldItemZValue.count();
    for (int i = 0; i < count; i++) {
        QGraphicsItem *item = m_oldItemZValue.keys().at(i);
        item->setZValue(m_oldItemZValue[item]);
        //myGraphicsScene->updateBlurItem(item);
        m_isRedoExcuteSuccess = true;
    }
    //重置保存的最大z值
    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            continue;
        }
        if (allItem->zValue() > myGraphicsScene->getMaxZValue()) {
            myGraphicsScene->setMaxZValue(allItem->zValue());
        }
    }

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (m_isRedoExcuteSuccess) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }
    myGraphicsScene->updateBlurItem();
}

void COneLayerDownCommand::redo()
{
    qDebug() << "COneLayerDownCommand::redo";
    if (!m_isUndoExcuteSuccess) {
        return;
    }

    m_isRedoExcuteSuccess = false;
    //移除z值为0的和多选管理图元
    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        if (allItems.at(i)->zValue() == 0.0) {
            allItems.removeAt(i);
            continue;
        }
        if (allItems[i]->type() <= QGraphicsItem::UserType || allItems[i]->type() >= EGraphicUserType::MgrType) {
            allItems.removeAt(i);
//            int count = allItems.size();
//            qDebug() << "count = " << count;
            continue;
        }
    }
    qSort(m_selectItems.begin(), m_selectItems.end(), zValueSortDES);
    QGraphicsItem *selectItemNext = nullptr;
    for (int selectIndex = 0; selectIndex < m_selectItems.size(); selectIndex++) {
        QGraphicsItem *selectItem = m_selectItems.at(selectIndex);
        selectItemNext = nullptr;
        if ((selectIndex + 1) < m_selectItems.size()) {
            selectItemNext = m_selectItems.at(selectIndex + 1);
        }
        m_isRedoExcuteSuccess = true;
        qSort(allItems.begin(), allItems.end(), zValueSortDES);
        for (int allItemIndex = 0; allItemIndex < allItems.size(); allItemIndex++) {
            QGraphicsItem *allItem = allItems.at(allItemIndex);
            if (allItem->zValue() < selectItem->zValue()) {
                if (allItem == selectItemNext) {
                    break;
                }
                //记录原来z值
                m_oldItemZValue[allItem] = allItem->zValue();
                m_oldItemZValue[selectItem] = selectItem->zValue();

                qreal tmpZValue = selectItem->zValue();
                selectItem->setZValue(allItem->zValue());
                allItem->setZValue(tmpZValue);
                break;
            }
        }
    }
    //重置保存的最大z值
    allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            continue;
        }
        if (allItem->zValue() > myGraphicsScene->getMaxZValue()) {
            myGraphicsScene->setMaxZValue(allItem->zValue());
        }
    }

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (m_isRedoExcuteSuccess) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }

    myGraphicsScene->updateBlurItem();
}

CBringToFrontCommand::CBringToFrontCommand(CDrawScene *scene, const QList<QGraphicsItem *> &items, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    for (auto item : scene->items()) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            if (items.contains(item)) {
                m_items.append(item);
            }
        }
    }
    QList<QGraphicsItem *> curItems;
    for (auto item : scene->items(Qt::AscendingOrder)) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            if (curItems.isEmpty()) {
                if (items.contains(item)) {
                    curItems.append(item);
                }
            } else {
                if (items.contains(item)) {
                    curItems.append(item);
                } else {
                    m_changedItems.append(qMakePair<QGraphicsItem *, QList<QGraphicsItem *>>(item, curItems));
                    curItems.clear();
                }
            }
        }
    }
    for (auto item : items) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            m_oldItemZValue[item] = item->zValue();
        }
    }
    m_selectItems = items;
}

void CBringToFrontCommand::undo()
{
    bool modifyFlag = false;
    int count = m_oldItemZValue.count();
    for (int i = 0; i < count; i++) {
        QGraphicsItem *item = m_oldItemZValue.keys().at(i);
        item->setZValue(m_oldItemZValue[item]);
        modifyFlag = true;
    }
    //重置保存的最大z值
    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            continue;
        }
        if (allItem->zValue() > myGraphicsScene->getMaxZValue()) {
            myGraphicsScene->setMaxZValue(allItem->zValue());
        }
    }

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (modifyFlag) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }

    myGraphicsScene->updateBlurItem();
}

void CBringToFrontCommand::redo()
{
    bool modifyFlag = false;

    qSort(m_selectItems.begin(), m_selectItems.end(), zValueSortASC);
    qreal maxZValue = myGraphicsScene->getMaxZValue();
    for (int selectIndex = 0; selectIndex < m_selectItems.size(); selectIndex++) {
        QGraphicsItem *selectItem = m_selectItems.at(selectIndex);
        maxZValue = myGraphicsScene->getMaxZValue();
        selectItem->setZValue(maxZValue + 1);
        myGraphicsScene->setMaxZValue(maxZValue + 1);
        modifyFlag = true;
    }

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (modifyFlag) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }
    myGraphicsScene->updateBlurItem();
}

CSendToBackCommand::CSendToBackCommand(CDrawScene *scene, const QList<QGraphicsItem *> &items, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    for (auto item : scene->items()) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            if (items.contains(item)) {
                m_items.append(item);
            }
        }
    }
    QList<QGraphicsItem *> curItems;
    QGraphicsItem *preItem = nullptr;
    for (auto item : scene->items(Qt::AscendingOrder)) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            if (items.contains(item)) {
                if (preItem != nullptr) {
                    curItems.append(item);
                }
            } else {
                if (!curItems.isEmpty()) {
                    m_changedItems.append(qMakePair<QGraphicsItem *, QList<QGraphicsItem *>>(preItem, curItems));
                    curItems.clear();
                }
                preItem = item;
            }
        }
    }
    if (preItem != nullptr && !curItems.isEmpty()) {
        m_changedItems.append(qMakePair<QGraphicsItem *, QList<QGraphicsItem *>>(preItem, curItems));
    }
    m_oldItemZValue.clear();
    for (auto item : items) {
        if (item->type() > QGraphicsItem::UserType && item->type() < EGraphicUserType::MgrType) {
            m_oldItemZValue[item] = item->zValue();
        }
    }
    m_selectItems = items;
}

CSendToBackCommand::~CSendToBackCommand()
{
}

void CSendToBackCommand::undo()
{
    qDebug() << "CSendToBackCommand::undo";

    bool modifyFlag = false;
    int count = m_oldItemZValue.count();
    for (int i = 0; i < count; i++) {
        QGraphicsItem *item = m_oldItemZValue.keys().at(i);
        item->setZValue(m_oldItemZValue[item]);
        //myGraphicsScene->updateBlurItem(item);
        modifyFlag = true;
    }
    //重置保存的最大z值
    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    qreal maxZvalue = 0;
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            continue;
        }
        if (allItem->zValue() > maxZvalue) {
            maxZvalue = allItem->zValue();
        }
    }
    myGraphicsScene->setMaxZValue(maxZvalue);

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (modifyFlag) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }
    myGraphicsScene->updateBlurItem();
}

void CSendToBackCommand::redo()
{
    qDebug() << "CSendToBackCommand::redo";

    bool modifyFlag = false;

    QList<QGraphicsItem *> allItems = myGraphicsScene->items();
    for (int i = allItems.size() - 1; i >= 0; i--) {
        QGraphicsItem *allItem = allItems.at(i);
        if (allItems.at(i)->zValue() == 0.0) {
            allItems.removeAt(i);
            continue;
        }
        if (allItem->type() <= QGraphicsItem::UserType || allItem->type() >= EGraphicUserType::MgrType) {
            allItems.removeAt(i);
            continue;
        }
        for (int j = 0; j < m_selectItems.size(); j++) {
            QGraphicsItem *selectItem = m_selectItems.at(j);
            if (allItem == selectItem) {
                allItems.removeAt(i);
                break;
            }
        }
    }

    qSort(m_selectItems.begin(), m_selectItems.end(), zValueSortASC);
    myGraphicsScene->setMaxZValue(m_selectItems.last()->zValue());
    qSort(allItems.begin(), allItems.end(), zValueSortASC);
    for (int allItemIndex = 0; allItemIndex < allItems.size(); allItemIndex++) {
        QGraphicsItem *allItem = allItems.at(allItemIndex);
        m_oldItemZValue[allItem] = allItem->zValue();
        allItem->setZValue(myGraphicsScene->getMaxZValue() + 1);
        myGraphicsScene->setMaxZValue(myGraphicsScene->getMaxZValue() + 1);

        modifyFlag = true;
    }

    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();

    if (modifyFlag) {
        myGraphicsScene->update();
        myGraphicsScene->setModify(true);
    }
    myGraphicsScene->updateBlurItem();
}

//CSetBlurAttributeCommand::CSetBlurAttributeCommand(CDrawScene *scene, CGraphicsMasicoItem *item, int newType, int newRadio, QUndoCommand *parent)
//    : QUndoCommand(parent)
//    , m_pItem(item)
//    , m_nNewType(newType)
//    , m_nNewRadius(newRadio)
//{
//    myGraphicsScene = scene;
//    m_nOldType = item->getBlurEffect();
//    m_nOldRadius = item->getBlurWidth();
//}

//void CSetBlurAttributeCommand::undo()
//{
//    m_pItem->setBlurEffect(static_cast<EBlurEffect>(m_nOldType));
//    m_pItem->setBlurWidth(m_nOldRadius);
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//}

//void CSetBlurAttributeCommand::redo()
//{
//    m_pItem->setBlurEffect(static_cast<EBlurEffect>(m_nNewType));
//    m_pItem->setBlurWidth(m_nNewRadius);
//    myGraphicsScene->clearSelection();
//    m_pItem->setSelected(true);
//    myGraphicsScene->setModify(true);
//    CManagerAttributeService::getInstance()->refreshSelectedCommonProperty();
//}

CSceneCutCommand::CSceneCutCommand(CDrawScene *scene, QRectF rect, QUndoCommand *parent, CGraphicsItem *item)
    : QUndoCommand(parent)
    , m_newRect(rect)
    , m_oldRect(scene->sceneRect())
{
    myGraphicsScene = scene;
//    m_oldRect = scene->sceneRect();
    m_item = item;
}

CSceneCutCommand::~CSceneCutCommand()
{
}

void CSceneCutCommand::undo()
{
    myGraphicsScene->setSceneRect(m_oldRect);
    myGraphicsScene->update();

    myGraphicsScene->updateBlurItem();
}

void CSceneCutCommand::redo()
{
    myGraphicsScene->setSceneRect(m_newRect);
    myGraphicsScene->update();

    myGraphicsScene->updateBlurItem();
}

CItemsAlignCommand::CItemsAlignCommand(CDrawScene *scene, QMap<CGraphicsItem *, QPointF> startPos, QMap<CGraphicsItem *, QPointF> endPos)
    : myGraphicsScene(scene)
    , m_itemsStartPos(startPos)
{
    m_itemsEndPos = endPos;
    m_isMoved = true;
}

void CItemsAlignCommand::undo()
{
    qDebug() << "CItemsAlignCommand::undo";
    if (m_isMoved) {
        QList<CGraphicsItem *> allItems = m_itemsStartPos.keys();
        QList<QPointF> itemsStartPos = m_itemsStartPos.values();
        QList<QPointF> itemsEndPos = m_itemsEndPos.values();

        for (int i = 0; i < allItems.size(); i++) {
            allItems.at(i)->move(itemsEndPos.at(i), itemsStartPos.at(i));
        }
    }
    m_isMoved = false;

    // 手动刷新重做后的多选框线
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();
}

void CItemsAlignCommand::redo()
{
    qDebug() << "CItemsAlignCommand::redo";
    if (!m_isMoved) {
        QList<CGraphicsItem *> allItems = m_itemsStartPos.keys();
        QList<QPointF> itemsStartPos = m_itemsStartPos.values();
        QList<QPointF> itemsEndPos = m_itemsEndPos.values();

        for (int i = 0; i < allItems.size(); i++) {
            allItems.at(i)->move(itemsStartPos.at(i), itemsEndPos.at(i));
        }
    }
    m_isMoved = true;

    // 手动刷新重做后的多选框线
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();
}

//CItemRotationCommand::CItemRotationCommand(CDrawScene *scene, CGraphicsItem *item, ERotationType endType)
//    : myGraphicsScene(scene)
//{
////    myGraphicsScene = scene;
//    m_item = item;
//    m_endType = endType;
//}

//void CItemRotationCommand::undo()
//{
//    qDebug() << "CItemsRotationCommand: "
//             << "undo";

//    // 只有图片才进行旋转操作
//    CPictureItem *pictureItem = static_cast<CPictureItem *>(m_item);
//    if (pictureItem) {
//        switch (m_endType) {
//        case ERotationType::LeftRotate_90:
//            pictureItem->setRotation90(false);
//            break;
//        case ERotationType::RightRotate_90:
//            pictureItem->setRotation90(true);
//            break;
//        case ERotationType::FlipHorizontal:
//            //pictureItem->setMirror(true, false);
//            break;
//        case ERotationType::FlipVertical:
//            //pictureItem->setMirror(false, true);
//            break;
//        default:
//            break;
//        }
//    }

//    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->getItemsMgr()->updateBoundingRect();
//    CManageViewSigleton::GetInstance()->getCurView()->drawScene()->refreshLook();
//}

//void CItemRotationCommand::redo()
//{
//    qDebug() << "CItemsRotationCommand: "
//             << "redo";

//    // 只有图片才进行旋转操作
//    CPictureItem *pictureItem = static_cast<CPictureItem *>(m_item);
//    if (pictureItem) {
//        switch (m_endType) {
//        case ERotationType::LeftRotate_90:
//            pictureItem->setRotation90(true);
//            break;
//        case ERotationType::RightRotate_90:
//            pictureItem->setRotation90(false);
//            break;
//        case ERotationType::FlipHorizontal:
//            //pictureItem->setMirror(true, false);
//            break;
//        case ERotationType::FlipVertical:
//            //pictureItem->setMirror(false, true);
//            break;
//        default:
//            break;
//        }
//    }
//}
