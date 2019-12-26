#include "Graphics.h"
#include "common.h"
#include   <bios.h> 

#define HOVERCOLOR 6
#define NORMALCOLOR 9

/* 按钮结构体 */
typedef struct tagButton
{
    int x;
    int y;
    int width;
    int height;
    char title[20];
    void (*OnClick)( struct tagButton *);
    void (*OnHover)( struct tagButton *);
    void (*OnLeave)( struct tagButton *);
}Button;

/*对按钮的初始化*/
Button   btn[9];
int Btnpos = 0;
/*按钮的标题*/
char * btn_Title[9]={"New Tree","PerOrder","InOrder","PosOrder","Insert","FindNode","Delete","ShowLeaf","Exit CAI"};

void OnHover( struct tagButton *);
void OnLeave( struct tagButton *);

/* 地图初始化 */
void map();
void GraphicsAdapter();
void InitialButton();

main()
{
    int key = 0;
    GraphicsAdapter();  /*初始化图形显示*/
/* */
    InitDrawData();
    InitTreeData();
    map();  

    MessageBox( "      -----------------Welcome To Use Lee CAI-------------------");
    while(1)
    {   	

             if( kbhit() )
             {
                 key=bioskey(0) ;
        		 
                 if( 0x4d00==key  && ( Btnpos <= 7 ) )		/* 向左 */
        		{
                            btn[Btnpos].OnLeave(&btn[Btnpos]);
                			Btnpos++;
                            btn[Btnpos].OnHover(&btn[Btnpos]);			
        		}
    	
                if( 0x4b00==key && (Btnpos >= 1 ))		/* 向右 */
        		{
                            btn[Btnpos].OnLeave(&btn[Btnpos]);
                			Btnpos--;
                            btn[Btnpos].OnHover(&btn[Btnpos]);	
        		}
        				
                if(0x1c0d==key && (Btnpos >=0 ))		/* 回车 对应的按钮处理*/
        		{	

                            btn[Btnpos].OnClick(&btn[Btnpos]);	
        		}	

                if(0x011b==key)				/*ECS 退出*/
        		{
                	exit(1);
        		}
             }  
    		 
    	}
    
    getch();
    closegraph();  
}

void map()
{
        /* 按钮框 */
        int i = 0;

        /* 初始化按钮*/	
        InitialButton();
    	/*绘制按钮*/
        for( i =0; i< 9; i++)
    	{
            btn[i].OnLeave(&btn[i]);
    	}
    	
        Btnpos  = 0;
        btn[Btnpos].OnHover(&btn[Btnpos]);
    	
        /* 命令框 */
        setcolor(3);/* 蓝色 */
        rectangle(0,38,639,38+21);
    	
        /* 树的基本信息框 */
        setcolor(4);/* 红色 */
        rectangle(4,67,640-4,87);

        /* 画树的区域 框*/
        setcolor(2);/* Green色 */
        rectangle(0,61,639,479); 
    	
    	
        m_ScreenX = 0;
        m_ScreenY = 62; 

}

/*对按钮进行初始化，*/
void InitialButton()
{
    int i = 0 ;
    for(i = 0 ; i < 9 ;i ++)
    {
        btn[i].x = 0 + i * 71;
        btn[i].y = 3;
    	
        btn[i].width = 70;
        btn[i].height = 30;	
        btn[i].OnHover = OnHover;
        btn[i].OnLeave = OnLeave;
        strcpy( &(btn[i].title) , btn_Title[i]);
        btn[i].OnClick = 0;
    }

    btn[8].width ++;

    /*给按钮添加对应的响应函数*/
    btn[0].OnClick = OnButtonCreatetree;
    btn[1].OnClick = OnButtonPreorder;
    btn[2].OnClick = OnButtonInorder;
    btn[3].OnClick = OnButtonPosorder;
    btn[4].OnClick = OnButtonInsertnode;
    btn[5].OnClick = OnButtonFindnode;
    btn[6].OnClick = OnButtonDeletenode;
    btn[7].OnClick = OnButtonIdentityLeaf;
    btn[8].OnClick = OnButtonExit;
}

/*按钮得到焦点的状态*/
void OnHover( Button * btn)
{
      setfillstyle(SOLID_FILL,HOVERCOLOR);/* 黄色背景 */
      bar(btn->x,btn->y,btn->x + btn->width,btn->y + btn->height);  
      setcolor(15); /* 白色按钮上的字 */
      outtextxy(btn->x + 5,btn->y + btn->height / 2,(char *)&(btn->title));
}

/*按钮失去焦点的状态*/
void OnLeave( Button * btn)
{
      setfillstyle(SOLID_FILL,NORMALCOLOR);/* 蓝色背景 */
      bar(btn->x,btn->y,btn->x + btn->width,btn->y + btn->height);  
      setcolor(7);  /* 白色按钮上的字 */
      outtextxy(btn->x + 5,btn->y + btn->height / 2,(char *)&(btn->title));
}


void GraphicsAdapter()
{
     int gdr;   /*测试硬件设备，管理显卡*/
     int gde;   /**/
     detectgraph(&gdr,&gde);

     switch(gdr)
     {
        case CGA: gde=1 ;
                break;

        case VGA: gde=2 ;
                break;

        case EGA: gde=1 ;
                break;
        case -2:  printf("\nplease install a Graphic Adapter!\n");
                exit(1);
        default:  printf("\nGraphic Adapter is not EGA,VGA,or,CGA \n");
                break;
     }
     registerbgidriver(EGAVGA_driver);
     initgraph(&gdr,&gde,"C:\\Win-TC\\projects");
     cleardevice();
}
