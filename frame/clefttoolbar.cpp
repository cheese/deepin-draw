#include "clefttoolbar.h"

#include "widgets/ccheckbutton.h"
#include "utils/baseutils.h"
#include "drawshape/cdrawtoolfactory.h"
#include "drawshape/cdrawtoolmanagersigleton.h"
#include "drawshape/cdrawparamsigleton.h"

#include <DFileDialog>

#include <DWidget>
#include <DApplication>
#include <QVBoxLayout>
#include <QDebug>


const int BTN_SPACING = 1;

CLeftToolBar::CLeftToolBar(DWidget *parent)
    : DFrame(parent)
{
    setMaximumWidth(50);

    initUI();
    initConnection();
    initDrawTools();
}

CLeftToolBar::~CLeftToolBar()
{

}

void CLeftToolBar::mouseMoveEvent(QMouseEvent *event)
{
    //禁止拖动
    Q_UNUSED(event)
}

void CLeftToolBar::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    qApp->setOverrideCursor(Qt::ArrowCursor);
    DFrame::enterEvent(event);
}


void CLeftToolBar::initUI()
{

    setFixedWidth(58);
    QMap<CCheckButton::EButtonSattus, QString> pictureMap;

    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/picture tools_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/picture tools_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/picture tools_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/picture tools_active.svg");
    m_picBtn = new CCheckButton(pictureMap, this);
    m_picBtn->setToolTip(tr("Import"));
    m_actionButtons.append(m_picBtn);

    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/rectangle tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/rectangle tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/rectangle tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/rectangle tool_active.svg");
    m_rectBtn = new CCheckButton(pictureMap, this);
    m_rectBtn->setToolTip(tr("Rectangle"));
    m_actionButtons.append(m_rectBtn);

    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/round tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/round tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/round tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/round tool_active.svg");
    m_roundBtn = new CCheckButton(pictureMap, this);
    m_roundBtn->setToolTip(tr("Ellipse"));
    m_actionButtons.append(m_roundBtn);



    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/triangle tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/triangle tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/triangle tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/triangle tool_active.svg");
    m_triangleBtn = new CCheckButton(pictureMap, this);
    m_triangleBtn->setToolTip(tr("Triangle"));
    m_actionButtons.append(m_triangleBtn);



    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/star tool_normal.png");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/star tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/star tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/star tool_active.svg");
    m_starBtn = new CCheckButton(pictureMap, this);
    m_starBtn->setToolTip(tr("Star"));
    m_actionButtons.append(m_starBtn);



    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/hexagon tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/hexagon tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/hexagon tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/hexagon tool_active.svg");
    m_polygonBtn = new CCheckButton(pictureMap, this);
    m_polygonBtn->setToolTip(tr("Polygon"));
    m_actionButtons.append(m_polygonBtn);



    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/line tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/line tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/line tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/line tool_active.svg");
    m_lineBtn = new CCheckButton(pictureMap, this);
    m_lineBtn->setToolTip(tr("Line"));
    m_actionButtons.append(m_lineBtn);



    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/brush tool_normal.png");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/brush tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/brush tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/brush tool_active.svg");
    m_penBtn = new CCheckButton(pictureMap, this);
    m_penBtn->setToolTip(tr("Pencil"));
    m_actionButtons.append(m_penBtn);


    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/text tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/text tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/text tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/text tool_active.svg");
    m_textBtn = new CCheckButton(pictureMap, this);
    m_textBtn->setToolTip(tr("Text"));
    m_actionButtons.append(m_textBtn);


    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/smudge tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/smudge tool_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/smudge tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/smudge tool_active.svg");
    m_blurBtn = new CCheckButton(pictureMap, this);
    m_blurBtn->setToolTip(tr("Blur"));
    m_actionButtons.append(m_blurBtn);


    pictureMap[CCheckButton::Normal] = QString(":/theme/light/images/action/screenshot tool_normal.svg");
    pictureMap[CCheckButton::Hover] = QString(":/theme/light/images/action/screenshot too_hover.svg");
    pictureMap[CCheckButton::Press] = QString(":/theme/light/images/action/screenshot tool_press.svg");
    pictureMap[CCheckButton::Active] = QString(":/theme/light/images/action/screenshot tool_active.svg");
    m_cutBtn = new CCheckButton(pictureMap, this);
    m_cutBtn->setObjectName("CutBtn");
    m_cutBtn->setToolTip(tr("Cut"));
    m_actionButtons.append(m_cutBtn);

    m_layout = new QVBoxLayout(this);
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addStretch();
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_picBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_rectBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_roundBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_triangleBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_starBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_polygonBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_lineBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_penBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_textBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_blurBtn);
    m_layout->addSpacing(BTN_SPACING);
    m_layout->addWidget(m_cutBtn);
    m_layout->setContentsMargins(5, 0, 5, 0);
    m_layout->addStretch();
//    m_layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));

    setLayout(m_layout);
}

void CLeftToolBar::slotChangedStatusToSelect()
{
    foreach (CCheckButton *button, m_actionButtons) {
        if (button->isChecked()) {
            button->setChecked(false);
            return;
        }
    }
}


void CLeftToolBar::clearOtherSelections(CCheckButton *clickedButton)
{
    foreach (CCheckButton *button, m_actionButtons) {
        if (button->isChecked() && button != clickedButton) {
            button->setChecked(false);
            return;
        }
    };
}



void CLeftToolBar::initConnection()
{

    connect(m_picBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_picBtn);

        emit setCurrentDrawTool(importPicture);//modify to set currentDrawTool
        emit importPic();
        m_picBtn->setChecked(false);


    });




    connect(m_rectBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_rectBtn);
        emit setCurrentDrawTool(rectangle);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(rectangle);
    });

    connect(m_roundBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_roundBtn);
        emit setCurrentDrawTool(ellipse);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(ellipse);
    });

    connect(m_triangleBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_triangleBtn);
        emit setCurrentDrawTool(triangle);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(triangle);
    });

    connect(m_starBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_starBtn);
        emit setCurrentDrawTool(polygonalStar);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(polygonalStar);
    });

    connect(m_polygonBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_polygonBtn);
        emit setCurrentDrawTool(polygon);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(polygon);

    });

    connect(m_lineBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_lineBtn);
        emit setCurrentDrawTool(line);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(line);

    });

    connect(m_penBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_penBtn);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(pen);
        emit setCurrentDrawTool(pen);

    });

    connect(m_textBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_textBtn);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(text);
        emit setCurrentDrawTool(text);

    });

    connect(m_blurBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_blurBtn);
        emit setCurrentDrawTool(blur);

    });

    connect(m_cutBtn, &CCheckButton::buttonClick, [this]() {
        clearOtherSelections(m_cutBtn);
        CDrawParamSigleton::GetInstance()->setCurrentDrawToolMode(cut);
        emit setCurrentDrawTool(cut);
    });
}

void CLeftToolBar::initDrawTools()
{
    IDrawTool *pTool = CDrawToolFactory::Create(selection);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(selection, pTool);
    pTool = CDrawToolFactory::Create(rectangle);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(rectangle, pTool);
    pTool = CDrawToolFactory::Create(ellipse);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(ellipse, pTool);
    pTool = CDrawToolFactory::Create(line);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(line, pTool);
    pTool = CDrawToolFactory::Create(triangle);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(triangle, pTool);
    pTool = CDrawToolFactory::Create(text);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(text, pTool);
    pTool = CDrawToolFactory::Create(polygon);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(polygon, pTool);
    pTool = CDrawToolFactory::Create(polygonalStar);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(polygonalStar, pTool);
    pTool = CDrawToolFactory::Create(pen);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(pen, pTool);
    pTool = CDrawToolFactory::Create(cut);
    CDrawToolManagerSigleton::GetInstance()->insertDrawTool(cut, pTool);
}
