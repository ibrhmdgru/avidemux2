/***************************************************************************
                          DIA_crop.cpp  -  description
                             -------------------

			    GUI for cropping including autocrop
			    +Revisted the Gtk2 way
			     +Autocrop now in RGB space (more accurate)

    begin                : Fri May 3 2002
    copyright            : (C) 2002/2007 by mean
    email                : fixounet@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Q_mpdelogo.h"
#include "ADM_toolkitQt.h"

//
//	Video is in YV12 Colorspace
//
//
/**

*/

  Ui_mpdelogoWindow::Ui_mpdelogoWindow(QWidget *parent,  delogo *param, ADM_coreVideoFilter *in) 
            : QDialog(parent)
  {
    uint32_t width,height;
        ui.setupUi(this);
        lock=0;
        // Allocate space for green-ised video
        width=in->getInfo()->width;
        height=in->getInfo()->height;

        canvas=new ADM_QCanvas(ui.graphicsView,width,height);
        
        myCrop=new flyMpDelogo( width, height,in,canvas,ui.horizontalSlider);
        memcpy(&(myCrop->param),param,sizeof(delogo));
        myCrop->_cookie=&ui;
        myCrop->upload();
        myCrop->sliderChanged();


        connect( ui.horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderUpdate(int)));
#define SPINNER(x) connect( ui.doubleSpinBox##x,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int))); 
//          SPINNER(Treshold);
//          SPINNER(Strength);
//          SPINNER(Block);
//          connect( ui.checkBox,SIGNAL(stateChanged(int)),this,SLOT(valueChanged(int))); 

  }
/**

*/

  void Ui_mpdelogoWindow::sliderUpdate(int foo)
  {
    myCrop->sliderChanged();
  }
/**

*/

  void Ui_mpdelogoWindow::gather(delogo *param)
  {
    
        myCrop->download();
        memcpy(param,&(myCrop->param),sizeof(delogo));
  }
/**

*/
Ui_mpdelogoWindow::~Ui_mpdelogoWindow()
{
  if(myCrop) delete myCrop;
  myCrop=NULL; 
  if(canvas) delete canvas;
  canvas=NULL;
}
/**

*/

void Ui_mpdelogoWindow::valueChanged( int f )
{
  if(lock) return;
  lock++;
  myCrop->update();
  lock--;
}

#define MYSPIN(x) w->doubleSpinBox##x
//************************
/**

*/
uint8_t flyMpDelogo::upload(void)
{
#if 0
      Ui_asharpDialog *w=(Ui_asharpDialog *)_cookie;

        MYSPIN(Treshold)->setValue(param.t);
        MYSPIN(Strength)->setValue(param.d);
        MYSPIN(Block)->setValue(param.b);
        
        //w->bf->w->checkBox->isChecked();
        w->checkBox->setChecked(param.bf);
#endif
        printf("Upload\n");
        return 1;
}
/**

*/
uint8_t flyMpDelogo::download(void)
{
#if 0
       Ui_asharpDialog *w=(Ui_asharpDialog *)_cookie;
       param.t= MYSPIN(Treshold)->value();
       param.d= MYSPIN(Strength)->value();
       param.b= MYSPIN(Block)->value();
       
       //w->spinBoxBottom->setValue(bottom);
       param.bf=w->checkBox->isChecked();
#endif
        printf("Download\n");
}

/**
      \fn     DIA_getMpDelogo
      \brief  Handle delogo dialog
*/
bool DIA_getMpDelogo(delogo *param, ADM_coreVideoFilter *in)
{
        uint8_t ret=0;
        
        Ui_mpdelogoWindow dialog(qtLastRegisteredDialog(), param,in);
		qtRegisterDialog(&dialog);

        if(dialog.exec()==QDialog::Accepted)
        {
            dialog.gather(param); 
            ret=1;
        }

		qtUnregisterDialog(&dialog);
        return ret;
}

//____________________________________
// EOF


