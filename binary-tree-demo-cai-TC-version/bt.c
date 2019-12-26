#include "Graphics.h"
#include "common.h"
#include   <bios.h> 

#define HOVERCOLOR 6
#define NORMALCOLOR 9

/* ��ť�ṹ�� */
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

/*�԰�ť�ĳ�ʼ��*/
Button   btn[9];
int Btnpos = 0;
/*��ť�ı���*/
char * btn_Title[9]={"New Tree","PerOrder","InOrder","PosOrder","Insert","FindNode","Delete","ShowLeaf","Exit CAI"};

void OnHover( struct tagButton *);
void OnLeave( struct tagButton *);

/* ��ͼ��ʼ�� */
void map();
void GraphicsAdapter();
void InitialButton();

main()
{
    int key = 0;
    GraphicsAdapter();  /*��ʼ��ͼ����ʾ*/
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
        		 
                 if( 0x4d00==key  && ( Btnpos <= 7 ) )		/* ���� */
        		{
                            btn[Btnpos].OnLeave(&btn[Btnpos]);
                			Btnpos++;
                            btn[Btnpos].OnHover(&btn[Btnpos]);			
        		}
    	
                if( 0x4b00==key && (Btnpos >= 1 ))		/* ���� */
        		{
                            btn[Btnpos].OnLeave(&btn[Btnpos]);
                			Btnpos--;
                            btn[Btnpos].OnHover(&btn[Btnpos]);	
        		}
        				
                if(0x1c0d==key && (Btnpos >=0 ))		/* �س� ��Ӧ�İ�ť����*/
        		{	

                            btn[Btnpos].OnClick(&btn[Btnpos]);	
        		}	

                if(0x011b==key)				/*ECS �˳�*/
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
        /* ��ť�� */
        int i = 0;

        /* ��ʼ����ť*/	
        InitialButton();
    	/*���ư�ť*/
        for( i =0; i< 9; i++)
    	{
            btn[i].OnLeave(&btn[i]);
    	}
    	
        Btnpos  = 0;
        btn[Btnpos].OnHover(&btn[Btnpos]);
    	
        /* ����� */
        setcolor(3);/* ��ɫ */
        rectangle(0,38,639,38+21);
    	
        /* ���Ļ�����Ϣ�� */
        setcolor(4);/* ��ɫ */
        rectangle(4,67,640-4,87);

        /* ���������� ��*/
        setcolor(2);/* Greenɫ */
        rectangle(0,61,639,479); 
    	
    	
        m_ScreenX = 0;
        m_ScreenY = 62; 

}

/*�԰�ť���г�ʼ����*/
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

    /*����ť��Ӷ�Ӧ����Ӧ����*/
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

/*��ť�õ������״̬*/
void OnHover( Button * btn)
{
      setfillstyle(SOLID_FILL,HOVERCOLOR);/* ��ɫ���� */
      bar(btn->x,btn->y,btn->x + btn->width,btn->y + btn->height);  
      setcolor(15); /* ��ɫ��ť�ϵ��� */
      outtextxy(btn->x + 5,btn->y + btn->height / 2,(char *)&(btn->title));
}

/*��ťʧȥ�����״̬*/
void OnLeave( Button * btn)
{
      setfillstyle(SOLID_FILL,NORMALCOLOR);/* ��ɫ���� */
      bar(btn->x,btn->y,btn->x + btn->width,btn->y + btn->height);  
      setcolor(7);  /* ��ɫ��ť�ϵ��� */
      outtextxy(btn->x + 5,btn->y + btn->height / 2,(char *)&(btn->title));
}


void GraphicsAdapter()
{
     int gdr;   /*����Ӳ���豸�������Կ�*/
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
