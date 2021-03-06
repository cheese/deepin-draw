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
#ifndef CTEXTTOOL_H
#define CTEXTTOOL_H
#include "idrawtool.h"

class CTextTool : public IDrawTool
{
public:
    CTextTool();
    virtual ~CTextTool() override;

protected:
    /**
     * @brief toolFinish 工具执行的结束
     * @param event 事件
     * @param scene 场景
     */
    virtual void toolCreatItemFinish(CDrawToolEvent *event, ITERecordInfo *pInfo) override;

    /**
     * @brief toolFinish 创建图元
     * @param event 事件
     * @param scene 场景
     */
    virtual CGraphicsItem *creatItem(CDrawToolEvent *event) override;

    /**
     * @brief minMoveUpdateDistance　工具创造业务图元指针
     */

    virtual int minMoveUpdateDistance() override;

    /**
     * @brief isPressEventHandledByQt　鼠标点下是否要交给qt框架处理
     */
    virtual bool isPressEventHandledByQt(CDrawToolEvent *event, ITERecordInfo *pInfo) override;
};

#endif // CTEXTTOOL_H
