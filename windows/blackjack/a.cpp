#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<iostream>
using namespace std;


class card		//һ����
{
private:
	int name;	//name of the card
	int type;
	bool pn;	//positive and negative; 
public:
	string gen_nm();	//������ʾ���Ƶ��ַ���
	void set_name(int );
	void set_type(int );
	void set_pn(bool );
	int get_name();
	int get_type();
	bool get_pn(); 
};


class poke_card			//ģ��һ����
{
private:
	bool sig[52];		//�Ƿ��Ѿ�����
public:
	poke_card();
	card Generate(bool);	//��һ����
};




class person			//����
{
protected:
	string name;
	bool busted;
	int num;
	card own_cards[8];
public:
	void set_busted(bool n);
	bool get_busted();
	int gen_value();
	int get_num();
	void set_num(int);
	string get_name();
	void set_name(string);
	virtual void first_alloc(poke_card &);
	virtual void be_asked(poke_card &);
	virtual void print_card(bool );
};




class dealer:public person		//ׯ��
{
public:
	dealer();
	virtual void first_alloc(poke_card &);
	virtual void be_asked(class poke_card &);
	virtual void print_card(bool);
};




class player:public person		//���
{
public:
	player();
	void first_alloc(poke_card &);
	void be_asked(poke_card &);
	void print_card(bool);
};





class game			//��Ϸ��
{
private:
	int number;	//number of players
	dealer house;
	player players[7];
	poke_card cards;
public:
	void welcome();
	void distribute();
	void run();
};









/****************************************************************
			    card 
****************************************************************/

string card::gen_nm()
{
	string tmp;
	char a_s[2] = "t";
	switch(name)
	{
		case 1:	tmp = "A";
			break;
		case 10:tmp = "10";
			break;
		case 11:tmp = "J";
			break;
		case 12:tmp = "Q";
			break;
		case 13:tmp = "K";
			break;
		default:a_s[0] = 48 + name;
			tmp = a_s;
			break; 
	}
	switch(type)
	{
		case 1:tmp += "c";
			break;
		case 2:tmp += "d";
			break;
		case 3:tmp += "h";
			break;
		case 4:tmp += "s";
			break;
	}
	return tmp;
}
void card::set_name(int new_name)
{
	name = new_name;
}
void card::set_type(int new_type)
{
	type = new_type;
}
void card::set_pn(bool new_pn)
{
	pn = new_pn;
}
int card::get_name()
{	
	return name;
}
int card::get_type()
{
	return type;
}
bool card::get_pn()
{
	return pn;
}
/******************************************************************/
	/*********************************************/




/****************************************************************
			    poke_card 
****************************************************************/
poke_card::poke_card()
{
	int i;
	srand( time(0) );
	for (i=0; i<52; i++)
		sig[i] = false;
}
card poke_card::Generate(bool n_pn)
{
	int n,t;
	card tmp;
	do
	{				//���ѡ��һ����
		n = rand()%13+1 ;
		t = rand()%4+1 ;
		tmp.set_name( n );
		tmp.set_type( t );
		tmp.set_pn( n_pn );
	}while(sig[(n-1)*4 + t - 1] == true);
	sig[(n-1)*4 + t - 1] = true;
	return tmp;
}
/******************************************************************/
	     /****************************************/





/****************************************************************
			    person 
****************************************************************/
void person::set_busted(bool n)
{
	busted = n;
}
bool person::get_busted()
{
	return busted;
}
int person::gen_value()
{				//���������Ʋ�����21��ֵ������ֵ
	int ace_count= 0, count = 0;
	int i;	
	for( i=0; i<num; i++)		//����ace�� ����
	{
		if(own_cards[i].get_name() == 1)
			ace_count++;
	}
	for( i=0; i<num; i++)   	//��ace��11�㣬��������
	{
		if(own_cards[i].get_name() == 11 || own_cards[i].get_name() == 12 || own_cards[i].get_name() == 13 )
			count += 10;
		else if(own_cards[i].get_name() != 1)
			count += own_cards[i].get_name();
		else 
			count += 11;   //ace��11��
	}
	for(i=0; i<ace_count; i++)  //��ace��1�㿴�Ƿ�����С��21
	{
		if(count < 21 )
			break;
		count -=10;
	}
	return count;
}

int person::get_num()
{
	return num;
}
void person::set_num(int new_num)
{
	num = new_num;
}
string person::get_name()
{
	return name;
}
void person::set_name(string new_name)
{	
	name = new_name;
}
void person::first_alloc(poke_card &card){}
void person::be_asked(class poke_card &cards){}
void person::print_card(bool asked){}
/******************************************************************/
	     /****************************************/



 

/****************************************************************
			    dealer 
****************************************************************/
dealer::dealer()
{
	num = 0; 	
}
void dealer::first_alloc(poke_card &cards)
{
	num = 2;
	own_cards[0] = cards.Generate(false);
	own_cards[1] = cards.Generate(true);
	print_card(false);
}


void dealer::be_asked(class poke_card &cards)  	//��ѯ���Ƿ�Ҫ��
{
	char yn;
	int i;
	cout<<endl;
	print_card(true);
	while(1)
	{
		if( gen_value() <= 16)  //�ж��Ƿ����16
		{
			own_cards[num] = cards.Generate(true);
			num++;
			print_card(true);
			if( gen_value() > 21 )
				{
					cout<<name<<" busts."<<endl;
					set_busted(true);
					break;
				}
		}
		else
		{
			cout<<name<<", do you want a hit? <Y/N>:";
			cin>>yn;
			if(yn == 'n' || yn == 'N')
				break;
			else if(yn == 'y' || yn == 'Y')
			{
				own_cards[num] = cards.Generate(true);
				num++;
				print_card(true);
				if( gen_value() > 21 )
				{
					cout<<name<<" busts."<<endl;
					set_busted(true);
					break;
				}
			}
			else
			cout<<"invalid input?"<<endl;
		}
	}
}
void dealer::print_card(bool asked)
{
	int i;
	cout<<setw(8)<<setiosflags(ios::left)<<name + ":";
	if( num == 2 && asked == false )
		cout<<setw(8)<<"XX";
	else
		cout<<setw(8)<<own_cards[0].gen_nm();
	for (i=1 ;i<num; i++)
		cout<<setw(8)<<own_cards[i].gen_nm();
	if( num == 2 && asked == false )
		cout<<endl;
	else
		cout<<"    <"<<gen_value()<<">"<<endl;
}
/******************************************************************/
	     /****************************************/









/****************************************************************
			    player 
****************************************************************/
player::player()
{
	num = 0;
}
void player::first_alloc(poke_card &cards)
{
	num = 2;
	own_cards[0] = cards.Generate(true);
	own_cards[1] = cards.Generate(true);
	print_card(false);
}
void player::be_asked(poke_card &cards)
{
	char yn;
	int i;
	cout<<endl;
	print_card(true);
	while(1)
	{
		cout<<name<<", do you want a hit? <Y/N>:";
		cin>>yn;
		if(yn == 'n' || yn == 'N')
			break;
		else if(yn == 'y' || yn == 'Y')
		{
			own_cards[num] = cards.Generate(true);
			num++;
			print_card(true);
			if( gen_value() > 21 )
			{
				cout<<name<<" busts."<<endl;
				set_busted(true);
				break;
			}
		}
		else
			cout<<"invalid input?"<<endl;
	}
}
void player::print_card(bool asked)
{
	int i;
	cout<<setw(8)<<setiosflags(ios::left)<<name + ":";
	for (i=0 ;i<num; i++)
		cout<<setw(8)<<own_cards[i].gen_nm();
	cout<<"     <"<<gen_value()<<">"<<endl;
}
/******************************************************************/
	     /****************************************/






/****************************************************************
			     game
****************************************************************/
void game::welcome() 	//��ӭ����
{
	int i;
	string tmp;
	house.set_name("House");
	house.set_busted(false);
	cout<<"\t\tWelcome to Blackjack!\n"<<endl;
	while(1)
	{
		cout<<"How many players? <1 - 7>: ";
		cin>>number;
		if(number > 7 || number <1 )
			cout<<"invalid input"<<endl;
		else
			break;
	}	
	for( i=0; i < number; i++ )
	{
		cout<<"Enter player name:";
		cin>>tmp;
		players[i].set_name(tmp);
		players[i].set_busted(false);
	}
	cout<<endl;
}

void game::distribute()		//����
{
	int i;
	class person *p;
	poke_card &tmp = cards;
	p = players;
	for (i=0 ;i<number ;i++, p++)
	{
		p->first_alloc(tmp);
	}
	house.first_alloc(tmp);
}

void game::run()		//��ʼ����
{
	int i;
	char again ;
	poke_card &tmp = cards;
	while(1)
	{
		welcome();
		distribute();
		class person *p;
		p = players;
		for (i=0; i<number; i++ ,p++)
		{
			p->be_asked(tmp);
		}
		house.be_asked(tmp);

		//judge
		if( house.get_busted() == true)
		{	
			p = players;
			for (i=0; i<number; i++ ,p++)
			{
				if( p->get_busted() == false )
					cout<<p->get_name()<<" wins."<<endl;
			}
		}
		else
		{
			p = players;
			for (i=0; i<number; i++ ,p++)
			{
				if( p->get_busted() == false && p->gen_value() > house.gen_value() )
					cout<<p->get_name()<<" wins."<<endl;
			}
		}
		cout<<"\nDo you want to play again? <Y/N): ";
		cin>>again;
		if(again == 'n' || again == 'N')
		{
			cout<< "bye"<<endl;
			break;
		}
		else if( again == 'y' || again == 'Y')
			continue;
		else
			cout<<"invalid input"<<endl;

	}
}
/******************************************************************/
	     /****************************************/






int main()
{
	game test;
	test.run();
}

