#include <string.h>
#include <iostream>
#include "pole.h"
#include <sstream>
#include <math.h>
#include <fstream>

Pole::Pole()//Конструктор
{
	last_move_maker = 0 ;//Обеспечит то, что первым ходят белые

	//Верхняя строка с чёрными фигурами
	kl[0][7].figura = 4 ;
	kl[0][7].color = 0 ;

	kl[1][7].figura = 2 ;
	kl[1][7].color = 0 ;

	kl[2][7].figura = 3 ;
	kl[2][7].color = 0 ;

	kl[3][7].figura = 6 ;
	kl[3][7].color = 0 ;

	kl[4][7].figura = 5 ;
	kl[4][7].color = 0 ;

	kl[5][7].figura = 3 ;
	kl[5][7].color = 0 ;

	kl[6][7].figura = 2 ;
	kl[6][7].color = 0 ;

	kl[7][7].figura = 4 ;
	kl[7][7].color = 0 ;

	// Нижняя строка с белыми фигурами 

	kl[0][0].figura = 4 ;
	kl[0][0].color = 1 ;

	kl[1][0].figura = 2 ;
	kl[1][0].color = 1 ;

	kl[2][0].figura = 3 ;
	kl[2][0].color = 1 ;

	kl[3][0].figura = 6 ;
	kl[3][0].color = 1 ;

	kl[4][0].figura = 5 ;
	kl[4][0].color = 1 ;

	kl[5][0].figura = 3 ;
	kl[5][0].color = 1 ;

	kl[6][0].figura = 2 ;
	kl[6][0].color = 1 ;

	kl[7][0].figura = 4 ;
	kl[7][0].color = 1 ;

	int i=0,j=0;


	//Середина поля с  пустыми полями 

	for(i=2;i<6;i++)
	{
		for(j=0;j<8;j++)
		{
			kl[j][i].figura = 0;
			kl[j][i].color = 2;
		}
	}

	//Строка с чёрными пешками

	i=6;
	for(j=0;j<8;j++)
	{
		kl[j][i].figura = 1;
		kl[j][i].color = 0;
	}
	
	//Строка сбелыми пешками
	
	i=1;
	for(j=0;j<8;j++)
	{
		kl[j][i].figura = 1;
		kl[j][i].color = 1;
	}
	next=0;
	prev=0;
	type=0;
};


int Pole::maketurn( int x1,int y1,int x2,int y2)//Функция совершения хода
{
	//Проверка на непокидание поля
	if ((x1>=0)and(x1<=7)and(x2>=0)and(x2<=7)and(y1>=0)and(y1<=7)and(y2>=0)and(y2<=7))
	{
		if (kl[x1][y1].figura==0)//Присутсвие фигуры в точке отправления
			return 0;
		else
		{
			if (last_move_maker==kl[x1][y1].color)//Возможность хода этой стороны
				return 0;
			else
			{
				//Отсутсвие союзной фигуры в точке прибытия
				if (kl[x1][y1].color==kl[x2][y2].color)
					return 0;
				else //Непосредственно ходы каждой из фигур
				{
					if (kl[x1][y1].figura==1) //ПЕШКА
					{
						if (last_move_maker==0)
						{
							if (y1==1)
								if ((y2==3)&&(kl[x1][y1+1].figura==0)&&
								(kl[x1][y1+2].figura==0)&&(x1==x2))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=1;
									last_move_maker=1;
									return 1;
								}
								if ((y2==2)&&(x1==x2)&&(kl[x1][y1+1].figura==0))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=1;
									last_move_maker=1;
									return 1;
								}
								if ((y1==6)||(y1==0)||(y1==7))
									return 0;
								if ((y1==2)||(y1==3)||(y1==4)||(y1==5))
								{
									if ((kl[x1][y1+1].figura==0)&&(x1==x2)
									&&(y2-y1<2))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=1;
										last_move_maker=1;
										return 1;
									}
									if (((x2==x1+1)||(x2==x1-1))&&(y2==y1+1)
									&&(kl[x2][y2].figura!=0))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=1;
										last_move_maker=1;
										return 1;
									}
								}
							}
							if (last_move_maker==1)
							{
								if (y1==6)
								if ((y2==4)&&(kl[x1][y1-1].figura==0)
								&&(kl[x1][y1-2].figura==0)&&(x1==x2))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=0;
									last_move_maker=0;
									return 1;
								}
								if ((y2==5)&&(x1==x2)&&(kl[x1][y1-1].figura==0))
								{
									kl[x1][y1].figura=0;
									kl[x1][y1].color=2;
									kl[x2][y2].figura=1;
									kl[x2][y2].color=0;
									last_move_maker=0;
									return 1;
								}
								if ((y1==1)||(y1==0)||(y1==7))
										return 0;
								if ((y1==2)||(y1==3)||(y1==4)||(y1==5))
								{
									if ((kl[x1][y1-1].figura==0)
									&&(x1==x2)&&(y1-y2<2))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=0;
										last_move_maker=0;
										return 1;
									}
									if (((x2==x1+1)||(x2==x1-1))&&(y2==y1-1)&&(kl[x2][y2].figura!=0))
									{
										kl[x1][y1].figura=0;
										kl[x1][y1].color=2;
										kl[x2][y2].figura=1;
										kl[x2][y2].color=0;
										last_move_maker=0;
										return 1;
									}
								}
							}
							return 0;
						}


						if(kl[x1][y1].figura == 6)//КОРОЛЕВА
						{ 
		
							int i,j;

							//Если мы ходим на право 

							if((x2>x1) && (y2==y1))
							{ 

								for(i=x1+1;i<x2;i++)
								{
							   			
							   		if(kl[i][y1].figura!=0)
							   		{
								  		return 0;
								  	}
							  
							    }
							}	

							//Если мы ходим на лево 

							if(x2<x1 && y2==y1)
							{ 

								for(i=x1-1;i>x2;i--)
								{
							   			
							   		if(kl[i][y1].figura!=0)
							   		{
								  		return 0;
								  	}
							    }
							}	
							//Если мы ходим  вверх
							if(y2>y1 && x2==x1)
							{
								for(j=y1+1;j<y2;j++)
								{
							   		if(kl[x1][j].figura!=0)
								  		return 0;
							    }
							}	

							//Если мы ходим  вниз

							if(y2<y1 && x2==x1)
							{ 

								for(j=y1-1;j>y2;j--)
								{
							   			
							   		if(kl[x1][j].figura!=0)
							   		{
								  		return 0;
								  	}
							    }
							}	


							//Если мы ходим по диагонали вверх и вправо 

						    if((y2>y1) && (x2>x1))
						    { 

						        for(j=y1+1;j<y2;j++)
						        {
						            for(i=x1+1;i<x2;i++)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   

							//Если мы ходим по диагонали вниз и вправо 

						    if((y2<y1) && (x2>x1))
						    { 

						        for(j=y1-1;j>y2;j--)
						        {
						            for(i=x1+1;i<x2;i++)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   

							 //Если мы ходим по диагонали вверх и влево

						    if((y2>y1) && (x2<x1))
						    { 

						        for(j=y1+1;j<y2;j++)
						        {
						            for(i=x1-1;i>x2;i--)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   

							//Если мы ходим по диагонали вниз и влево

						    if((y2<y1) && (x2<x1))
						    { 

						        for(j=y1-1;j>y2;j--)
						        {
						            for(i=x1-1;i>x2;i--)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   


							//Меняем значение полей
							if((x1==x2)||(y1==y2) || ((abs(y2-y1))==(abs(x2-x1))))
							{
								kl[x2][y2].color=kl[x1][y1].color;
								kl[x2][y2].figura=kl[x1][y1].figura;
								last_move_maker=kl[x1][y1].color;
								kl[x1][y1].figura=0;
								kl[x1][y1].color=2;
								return 1;
							}

							return 0;
						}


						if(kl[x1][y1].figura == 3)//СЛОН
						{ 
		
							int i,j;

							//Если мы ходим по диагонали вверх и вправо 

						    if((y2>y1) && (x2>x1))
						    { 

						        for(j=y1+1;j<y2;j++)
						        {
						            for(i=x1+1;i<x2;i++)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   

							//Если мы ходим по диагонали вниз и вправо 

						    if((y2<y1) && (x2>x1))
						    { 

						        for(j=y1-1;j>y2;j--)
						        {
						            for(i=x1+1;i<x2;i++)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   

			 //Если мы ходим по диагонали вверх и влево

						    if((y2>y1) && (x2<x1))
						    { 

						        for(j=y1+1;j<y2;j++)
						        {
						            for(i=x1-1;i>x2;i--)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   

							//Если мы ходим по диагонали вниз и влево

						    if ((y2<y1) && (x2<x1))
						    { 

						        for(j = y1 - 1; j > y2;j--)
						        {
						            for(i = x1 - 1; i > x2; i--)
						            {
						                if(kl[i][j].figura!=0)
						                {
						                	return 0;
						                }
						            }
					   
						        }
						    }   


							//Меняем значение полей
							if(((abs(y2-y1))==(abs(x2-x1))))
							{
								kl[x2][y2].color=kl[x1][y1].color;
								kl[x2][y2].figura=kl[x1][y1].figura;
								last_move_maker=kl[x1][y1].color;
								kl[x1][y1].figura=0;
								kl[x1][y1].color=2;
								return 1;
							}

							return 0;
						}

				
					
						if(kl[x1][y1].figura == 4)//Ладья
						{ 
		
							int i,j;

					//Если мы ходим на право 

									if((x2>x1) && (y2==y1)){ 

										for(i=x1+1;i<x2;i++){
						   			
						   			if(kl[i][y1].figura!=0){
							  	return 0;
							  	}
						  
					        			}
					        		}	

					//Если мы ходим на лево 

						       if(x2<x1 && y2==y1){ 

										for(i=x1-1;i>x2;i--){
						   			
						   			if(kl[i][y1].figura!=0){
							  	return 0;
							  	}
					        			}
					        		}	
					//Если мы ходим  вверх
							if(y2>y1 && x2==x1){
								for(j=y1+1;j<y2;j++)
								{
						   			if(kl[x1][j].figura!=0)
							  			return 0;
					        			}
					        		}	

					//Если мы ходим  вниз

							if(y2<y1 && x2==x1){ 

								for(j=y1-1;j>y2;j--)
								{
						   			
						   			if(kl[x1][j].figura!=0)
						   			{
							  			return 0;
							  		}
					        			}
					        		}	

					//Меняем значение полей
					if ((x1==x2)or(y1==y2))
					{
					kl[x2][y2].color=kl[x1][y1].color;
					kl[x2][y2].figura=kl[x1][y1].figura;
					last_move_maker=kl[x1][y1].color;
					kl[x1][y1].figura=0;
					kl[x1][y1].color=2;

					return 1;
					}
					return 0;
					}
				
					if (kl[x1][y1].figura == 5){//КОРОЛЬ


						if (((x1 + 1 == x2) && (y1==y2)) || ((x1 + 1 == x2) && 
						(y1 + 1==y2)) || ((x1 + 1 == x2) && (y1 - 1==y2)) || 
						((x1 == x2) && (y1 + 1 ==y2)) || ((x1 == x2) && 
						(y1 - 1==y2)) || ((x1 - 1 == x2) && (y1==y2)) || 
						((x1 - 1 == x2) && (y1 + 1==y2)) || ((x1 - 1 == x2) && 
						(y1 - 1==y2))){
							kl[x2][y2].color = kl[x1][y1].color;
							kl[x2][y2].figura = kl[x1][y1].figura;
							kl[x1][y1].color = 2;
							kl[x1][y1].figura = 0;
							last_move_maker = abs(last_move_maker - 1);
	
							return 1;
						}

						}
				
					if (kl[x1][y1].figura==2)//КОНЬ
					{
						if ((((x1-x2)==1)and((y1-y2)==2))or(((x2-x1)==1)and
						((y1-y2)==2))or(((x1-x2)==2)and((y1-y2)==1))or
						(((x2-x1)==2)and((y1-y2)==1))or(((x1-x2)==1)and
						((y2-y1)==2))or(((x2-x1)==1)and((y2-y1)==2))or
						(((x1-x2)==2)and((y2-y1)==1))or(((x2-x1)==2)
						and((y2-y1)==1)))
						{
							kl[x1][y1].color=2;
							kl[x1][y1].figura=0;
							if (last_move_maker==0)
								last_move_maker=1;
							else
								last_move_maker=0;
							kl[x2][y2].color=last_move_maker;
							kl[x2][y2].figura=2;
							return 1;
						}
					return 0;
					
					
					
					
					}
					else
						return 0;
				
				
				
				
				
				}			
			
			}
		}
	}
	else
		return 0;
};

void Pole::print(int q){//если 1, то печатаем доску повернутую к первому игроку, если 2, то печатаем доску повернутую ко второму игроку, если 3, то печатаем доску так, чтобы ее лучше видел тот, чей ход сейчас.
	if (q==3)
	{
		if (last_move_maker==0)
		{
			cout<<endl;
			int i,j,x;
			for (i=7;i>=0;i--){
				for (j=0;j<8;j++){
					if (j == 0) cout<<' '<<(i+1)<<"   "<<'|';
					x=(kl[j][i].color)? (kl[j][i].figura): (-kl[j][i].figura);
					if (x<0){
						cout<<x<<'|';
					}
					else{
						cout<<x<<' '<<'|';
					}	
				}
				cout<<endl;
			}
			cout<<endl;
			char t;
			for (i=1;i<9;i++){
				t = char(i+96);
				if (i == 1) cout<<"      "<<t<<' ';
				else cout<<" "<<t<<' ';
		
			}
			cout<<endl;
		}

		//////
		else
		{
			int i,j,x;
			char t;
			cout<<endl;
			for (i=0;i<8;i++){
				for (j=7;j>=0;j--){
					if (j == 7) cout<<' '<<(i+1)<<"   "<<'|';
					//if (1-i ==j)
					x=(kl[j][i].color)? (kl[j][i].figura): (-kl[j][i].figura);
					//else
					//x=(kl[1-j][1 - i].color)? (kl[1-j][1-i].figura): (-kl[1-j][1-i].figura);
					if (x<0){
						cout<<x<<'|';
					}
					else{
						cout<<x<<' '<<'|';
					}	
				}
				cout<<endl;
			}
			cout<<endl;

			for (i=8;i>0;i--){
				t = char(i+96);
				if (i == 8) cout<<"      "<<t<<' ';
				else cout<<" "<<t<<' ';
		
			}
			cout<<endl;
		}
	}
	if (q==1)
	{
		cout<<endl;
		int i,j,x;
		for (i=7;i>=0;i--){
			for (j=0;j<8;j++){
				if (j == 0) cout<<' '<<(i+1)<<"   "<<'|';
				x=(kl[j][i].color)? (kl[j][i].figura): (-kl[j][i].figura);
				if (x<0){
					cout<<x<<'|';
				}
				else{
					cout<<x<<' '<<'|';
				}	
			}
			cout<<endl;
		}
		cout<<endl;
		char t;
		for (i=1;i<9;i++)
		{
			t = char(i+96);
			if (i == 1) cout<<"      "<<t<<' ';
			else cout<<" "<<t<<' ';
	
		}
		cout<<endl;
	}
	if (q==2)
	{
			int i,j,x;
			char t;
			cout<<endl;
			for (i=0;i<8;i++){
				for (j=7;j>=0;j--){
					if (j == 7) cout<<' '<<(i+1)<<"   "<<'|';
					//if (1-i ==j)
					x=(kl[j][i].color)? (kl[j][i].figura): (-kl[j][i].figura);
					//else
					//x=(kl[1-j][1 - i].color)? (kl[1-j][1-i].figura): (-kl[1-j][1-i].figura);
					if (x<0){
						cout<<x<<'|';
					}
					else{
						cout<<x<<' '<<'|';
					}	
				}
				cout<<endl;
			}
			cout<<endl;

			for (i=8;i>0;i--){
				t = char(i+96);
				if (i == 8) cout<<"      "<<t<<' ';
				else cout<<" "<<t<<' ';
		
			}
			cout<<endl;
	}
};

Pole Pole::operator=(Pole pole)
{
last_move_maker=pole.last_move_maker;
type=pole.type;
hod=pole.hod;
prev=pole.prev;
next=pole.next;
int i,e;
for (i=0;i<8;++i)
for (e=0;e<8;++e)
kl[i][e]=pole.kl[i][e];

}



	
	




