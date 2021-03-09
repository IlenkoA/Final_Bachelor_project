#include "w.h"

//#include <iostream>

// Конструктор фрейма
MyWin::MyWin(const wxString& title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(1000,1000)){
  // создали полоску для менюшки
    menubar = new wxMenuBar;
// создали менюшку
    file = new wxMenu;
    //добавили обработчик изображений

// закинули менюшку на полоску
// пока не работает (для "красоты")
   
    //file->Append(wxID_ANY, wxT("&New"));
    
    //file->AppendSeparator();
// Для всех пунктор меню указывем идентификатор чтобы
// связать обработчик событие с конкретным элементом
// добавили к менюшке раздел quit
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit"));
// добавили раздел load
    load = new wxMenuItem(file, ID_MENU_LOAD, wxT("&Load"));
    file->Append(load);
    file->Append(quit);
// Это еще один пункт меню
// пока тоже не работает
     //im = new wxMenu;
     //im->Append(wxID_ANY, wxT("Edit figure"));
     //im->Append(wxID_ANY, wxT("Rotate 90"));
// добавили оба пункта меню на полску меню    
     menubar->Append(file, wxT("&File"));
    // menubar->Append(im, wxT("&Edit"));

 // установили полоску в окно
    SetMenuBar(menubar);
// подключили менюшку exit
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnQuit));
// подключили load (идентификаторы такие же как и при создании каждого элемента)
   Connect(ID_MENU_LOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnLoad));
	//Connect(wxEVT_PAINT, wxPaintEventHandler(MyWin::OnPaint));
// создание панельки для текста, кнопок и рисовалки
    m_pan= new wxPanel(this,wxID_ANY);
// это тоже панель, но наша.
// помещаем ее нна панель m_pan и задаем указатель на главный фрейм
    dp=new Draw(m_pan,this);
// это окошко для текста. Тоже помещаем на m_pan
    //tc =  new wxTextCtrl(m_pan, -1, wxT(""), wxPoint(200, 10),wxSize(200,50)); 
// статус-бар будет внизу окна
    sb=CreateStatusBar();
    //sb->SetStatusText(wxString(wxT("что-то напишем и здесь")));
	etalon = new Pole;

    Maximize(true); 
};



void MyWin::OnLoad(wxCommandEvent& event){
// специальный класс для листания файлов 
  wxFileDialog * openFileDialog = new wxFileDialog(this);
// если все открывается, выберем имя файла
// Только имя!!!
  if (openFileDialog->ShowModal() == wxID_OK){
// Что выбрали, то и будет именем файла
// Запоминаем в строку
      fileName = openFileDialog->GetPath();
     /*sb->SetStatusText(fileName); 	
     khod = CheckDebut(fileName.ToStdString());
     wxString se;
     se<<khod;
     sb->SetStatusText(se);*/
// Загружаем содержимое в окно текста
      //tc->LoadFile(fileName);
// Теперь нужно получить данные из файла
// Создаем объект - файловый поток
      wxFileInputStream input(fileName);
// Чтобы он работал как текстовый файл, превращаем его в поток-текст
      wxTextInputStream intext(input);
    //int  x1,y1,x2,y2; 
// "обычным" образом считываем данные
	//while (1){
	 int x1,x2,y1,y2;
	char a,b;
	int check = 1;
	while (1)
	{
		intext>>a>>y1>>b>>y2;
		if (y1==228)
			break;
		x1=a-96;
		x2=b-96;
		etalon->next = new Pole;
		*(etalon->next) = *(etalon);
		etalon->next->next = 0;
		etalon->next->prev = etalon;
		etalon->hod.a = a;
		etalon->hod.b = b;
		etalon->hod.y1 = y1;
		etalon->hod.y2 = y2;
		etalon = etalon->next;
		check=etalon->maketurn(x1-1,y1-1,x2-1,y2-1);
		if (check == 0) break;
	}
	while (etalon->prev!=0)
	etalon=etalon->prev;
	dp->ScreenPrint(*etalon);
	wxString se;
	se<<check;
    sb->SetStatusText(se);
    khod = check;
	//}
// Это нужно для перерисовки окна, когда будем рисовать фигуру
      //dp->Refresh();
  //}
}
};

void MyWin::OnQuit(wxCommandEvent& event){
  Close(true);
};

// Конструктор нашего Draw
Draw::Draw(wxPanel *parent, MyWin *fr):wxPanel(parent, -1,wxPoint(0,0),wxSize(500,500),wxBORDER_SUNKEN){
// подключили панель к событиям рисования
    Connect(wxEVT_PAINT,wxPaintEventHandler(Draw::OnPaint));
	//Connect(wxEVT_TIMER, wxCommandEventHandler(Draw::OnTimer));
	Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(Draw::OnMouse));
	//tm = new wxTimer(this, 1);
	p1.x = 0;
	p1.y = 0;
	p2.x = 0;
	p2.y = 0;
	ch = 0;
    mn = fr;
};

// Свободная функция рисования прямоугольника
// Для рисования есть абстрактный класс wxDC
// У него много разных наследников
// Самый простой wxPaintDC
// Но мы сделаем функцию для всех наследников wxDC

// Функция OnPaint() сработает при любом рисовании окна:
// первое рисование, сложил-разложили
// или вызов функции Refresh()

void Draw::OnPaint(wxPaintEvent& event){
// положили планшет wxPaintDC на нашу панель
   wxPaintDC dc(this);
   
   	  //tm->Start(3000);
	  wxString str;
      //str<<wxT("x=")<<p.x<<wxT("y=")<<p.y;
      //mn->sb->SetStatusText(str);
      Pole pole;
      //ScreenPrint(pole);
// Установили цвет заливки
//dc.SetBrush(wxBrush(wxColour(101,67,33)));

};

 void Draw::OnMouse(wxMouseEvent &event){
    // получение координат мыши
    wxString str;
    wxPaintDC dc(this);
    if (mn->khod == 1){
    if (ch % 2 == 0){
    mx=event.GetX();
    my=event.GetY();
    p1.x=mx;
    p1.y=my;
    ch++;
	}
	else{
    mx=event.GetX();
    my=event.GetY();
    p2.x=mx;
    p2.y=my;
    ch++;
    mn->khod = 0;
    Hod hod = Coords_To_Hod(p1.x,p1.y, p2.x, p2.y);
    int jk = PlayDebut(mn->etalon, hod);
    if (jk==1) {
		 ScreenPrint(*(mn->etalon));
		//sleep(2);
		//dc.Clear();
	}
    if (jk == 2) mn->khod = 1;
    if (jk == 3){
		 ScreenPrint(*(mn->etalon));
		 mn->khod = 1;
	}
    //int check = PlayDebut((mn->fileName).ToStdString(), p1.x, p1.y, p2.x, p2.y);
    //str<<wxT("x1 = ")<<p1.x<<wxT("y1 = ")<<p1.y<<wxT("x2 = ")<<p2.x<<wxT("y2 = ")<<p2.y;
    //mn->sb->SetStatusText(str); 
   // str<<check;
    //mn->sb->SetStatusText(str); 
	}
}
    /*mx=event.GetX();
    my=event.GetY();
    p1.x=mx;
    p1.y=my;
    Hod hod = Coords_To_Hod(p1.x,p1.y, p1.x, p1.y);
    str<<wxT("")<<hod.a<<wxT(" ")<<hod.y1; 
    mn->sb->SetStatusText(str);   */
//}
};


int Draw::ScreenPrint( Pole pole ){	
	wxPaintDC dc(this);
	dc.Clear();
	wxPoint g;
	int i,j;
		g.x = 0;
		g.y = 0 ;
	image1 = new wxBitmap("1.jpg", wxBITMAP_TYPE_JPEG);
	dc.DrawBitmap(*(image1),g,false);
	for(int i = 0;i < 8;i++){
		for (int j = 0; j< 8; j++){
			if ((pole.kl[i][j].figura == 4) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("bR.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 4) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("wR.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 1) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("wP.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 1) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("bP.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 2) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("wN.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 2) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("bN.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 3) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("bB.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 3) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("wB.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 5) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("bK.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 5) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("wK.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			if ((pole.kl[i][j].figura == 6) and (pole.kl[i][j].color == 1) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("wQ.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
			
			if ((pole.kl[i][j].figura == 6) and (pole.kl[i][j].color == 0) ){
			wxPoint f;
			f.x = 28 + 55*i;
			f.y = 25 + 55*(7-j) ;
			image2 = new wxBitmap("bQ.png", wxBITMAP_TYPE_PNG);
			dc.DrawBitmap(*(image2),f,false);
			}
	}
	}

};



Hod Draw::Coords_To_Hod(int x1,int y1, int x2, int y2)
{
Hod hod;
hod.a=(x1-29)/55+97;
hod.b=(x2-29)/55+97;
hod.y1=7-((y1-26)/55)+1;
hod.y2=7-((y2-26)/55)+1;
return hod;
}

int Draw::PlayDebut(Pole *etalon, Hod hod)//имя дебюта
    {
    if (etalon->next==0)
    return 1;//дебют закончился
    else
    {
    if (((etalon->hod.a==hod.a)&&(etalon->hod.b==hod.b)&&(etalon->hod.y1==hod.y1)&&(etalon->hod.y2==hod.y2))!=1)
    {
    return 2;//Ход некоректен

    }
    }
    *etalon=*etalon->next;
    return 3;//Ход удался

}


