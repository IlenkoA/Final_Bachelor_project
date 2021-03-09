#include "w.h"

// запуск окна
IMPLEMENT_APP(Begin)

bool Begin::OnInit()
{
  MyWin *wind=new MyWin(wxT("Test"));
  wind->Show(true);
  return true;
};
