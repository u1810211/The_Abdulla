#include <iostream>
#include <stack>
#include <string>
#include <conio.h>

using namespace std;

struct node
{
	string data;
	struct node* next;
};

struct vertexlist
{
	struct node* vlisthead;
};

struct Graph
{
	struct vertexlist* vl;
};

struct node* NewNode(string value)
{
	struct node* newnode = new node;
	newnode->data = value;
	newnode->next = NULL;

	return newnode;
}


struct Graph* Copy(Graph *&graph, Graph *&Gnew)
{
	for(int i = 0; graph->vl[i].vlisthead != NULL; i++)
	{
		node* ptr; node* ptr_1;
		ptr_1 = (*graph).vl[i].vlisthead;
		Gnew->vl[i].vlisthead = ptr_1;
		ptr = ptr_1;;
		ptr_1 = ptr_1->next;
		while (ptr_1 != NULL)
		{
			node* newnode = NewNode(ptr_1->data);
			ptr = newnode;
			ptr = ptr->next;
			ptr_1 = ptr_1->next;
		}
	}
	return Gnew;
}

struct Graph* CreateGraph(size_t& Graphsize)
{
	struct Graph* vlist = new Graph;

	vlist->vl = new vertexlist[Graphsize + 2];

	for (int i = 0; i < Graphsize + 2; i++)
	{
		vlist->vl[i].vlisthead = NULL;
	}

	return vlist;
}



struct Graph* Recopy(Graph*& newGraph, Graph*& graph, int choice_1)
{
	for (int i = 0; graph->vl[i + 1].vlisthead != NULL; i++)
	{
		if (i == choice_1)
		{
			i++;
			node* ptr; node* ptr_1;
			ptr_1 = (*graph).vl[i].vlisthead;
			newGraph->vl[choice_1].vlisthead = ptr_1;
			ptr = ptr_1;
			while (ptr_1->next != NULL)
			{
				ptr_1 = ptr_1->next;
				node* newnode = NewNode(ptr_1->data);
				ptr = newnode;
				ptr = ptr->next;
			}choice_1++; i--;
		}
		else {
			node* ptr; node* ptr_1;
			ptr_1 = (*graph).vl[i].vlisthead;
			newGraph->vl[i].vlisthead = ptr_1;
			ptr = ptr_1; ptr_1 = ptr_1->next;
			while (ptr_1 != NULL)
			{
				node* newnode = NewNode(ptr_1->data);
				ptr = newnode;
				ptr = ptr->next;
				ptr_1 = ptr_1->next;
			}
		}
	}
	return newGraph;
}



char Menu();
void Create(Graph*& graph, size_t& Graphsize);
void Add_person(Graph *&graph, size_t& Graphsize);
void Addition_of_person(Graph *&graph, int &choice);
void Delete_person(Graph*& graph);
void Deletion(Graph*& graph, int &choice);
void Delete_section(Graph*& graph, size_t Graphsize);
void Display_section(Graph*& graph);
void Display_graph(Graph*& graph);
void Check_section(Graph*& graph, int &check);


void Create(Graph *&graph, size_t& Graphsize)
{
	system("cls");
	cout << "\n\n\n\t\tChoose option of adding a hobby\n\n\n\t\t1) Single addition\n\n\n\t\t2)Multiple addition\n";
	string choice; cout << "\n\n\n\t\tOption: "; cin >> choice;
	int i = 0;
	string name; Graphsize = 0;
	stack<string> Fstack, Sstack;
	if (choice == "1")
	{
		cout << "\n\n\n\t\tGive a hobby: "; cin.ignore(); getline(cin, name);
		while (graph->vl[Graphsize].vlisthead != NULL)
		{
			Graphsize++;
		}
		node* newnode = NewNode(name);
		graph->vl[Graphsize].vlisthead = newnode;
		graph->vl[Graphsize].vlisthead->next = NULL;
		graph->vl[Graphsize + 1].vlisthead = NULL;
		Graph* Gnew = CreateGraph(Graphsize);
		Gnew = Copy(graph, Gnew);
		free(graph);
		graph = CreateGraph(Graphsize);
		graph = Copy(Gnew, graph);
		free(Gnew);
	}
	else if (choice == "2")
	{
		int t = 0;
		cout << "\n\n\n\t\tIf you want to stop adding a hobbies then push 'zero' \n\n";

		for (int i = 0; name != "0"; i++)
		{
			cout << "\t\t" << i + 1 << ") hobby: "; cin.ignore();
			cin >> name;
			if (name != "0") Sstack.push(name);
		}
		while (graph->vl[t].vlisthead != NULL) t++;
		Graphsize = Sstack.size() + t + 1;
		Graph* Gnew = CreateGraph(Graphsize);
		Gnew = Copy(graph, Gnew);
		free(graph);
		graph = CreateGraph(Graphsize);
		graph = Copy(Gnew, graph);
		while (!Sstack.empty())
		{
			name = Sstack.top(); Fstack.push(name); Sstack.pop();
		}
		while (!Fstack.empty())
		{
			name = Fstack.top();
			node* newnode = NewNode(name);
			graph->vl[t].vlisthead = newnode;
			Fstack.pop();
			graph->vl[t].vlisthead->next = NULL;
			t++;
		}
		graph->vl[t + 1].vlisthead = NULL;
		free(Gnew);
	}
	else {
		cout << "\n\n\n\t\tInvalid input\n"; _getch();
		system("cls");
		Create(graph, Graphsize);
	}
}

void Addition_of_person(Graph *&graph, int &choice)
{
	system("cls");
	cout << "\n\n\n\t\tChoose option of adding a person\n\n\n\t\t1) Single addition\n\n\n\t\t2) Multiple addition\n";
	string Mychoice; cout << "\t\tOption: "; cin >> Mychoice;
	string name; size_t Graphsize = 0;
	stack<string> Myname, Myname_1;
	if (Mychoice == "1")
	{
		cout << "\t\tGive a name of a person: "; cin >> name;
		node** current;
		current = &(graph)->vl[choice].vlisthead;
		Graph* Mynode = CreateGraph(Graphsize);
		while ((*current)->next != NULL)
			current = &(*current)->next;
		node* newnode1 = NewNode(name);
		(*current)->next = newnode1;
		current = &(*current)->next;
		(*current)->next = NULL;
		
	}
	else if (Mychoice == "2")
	{
		cout << "\n\t\tIf you want to stop adding a person then push 'zero'\n\n";
		for (int i = 0; name != "0"; i++)
		{
			cout << "\t\t" << i + 1 << ") Name: "; cin >> name;
			if (name != "0") Myname.push(name);
		}
		node** current;
		current = &(graph)->vl[choice].vlisthead;
		while (!Myname.empty()) { name = Myname.top(); Myname_1.push(name); Myname.pop();}
		while ((*current)->next != NULL)
			current = &(*current)->next;
		while (!Myname_1.empty())
		{
			node* newnode = NewNode(Myname_1.top());
			(*current)->next = newnode;
			current = &(*current)->next;
			(*current)->next = NULL;
			Myname_1.pop();
		}
	}

	else {
		cout << "\n\n\n\t\tInvalid input\n"; _getch();
		system("cls");
		Addition_of_person(graph, choice);
	}
}

void Add_person(Graph *&graph, size_t &Graphsize)
{
	int counter = 0, choice;
	string name;
	char option;
	if (!graph->vl[0].vlisthead == NULL) 
	{
		cout << "\n\n\n\t\tChoose a hobby to where you want to add a person\n\n";
		for (int i = 0; graph->vl[i].vlisthead != NULL; i++)
		{
			if (graph->vl[i].vlisthead != NULL)
			{
				counter++;
				cout << "\t" << i + 1 << ") List " << graph->vl[i].vlisthead->data << "\n";
			}
		}
		cout << "\t\tChoose ---> "; cin >> choice; choice -= 1;
		Addition_of_person(graph, choice);
	}
	else{
		cout << "\n\n\n\t\tThe list of hobbies is empty\n\t\tDo you want to add a hobby?\n\n\t\tChoose ---> Y/N: ";
		cin >> option;
		if (option == 'Y' || option == 'y') { system("cls"); Create(graph, Graphsize); }
		else system("cls");
	}
}


void Delete_person(Graph*& graph)
{
	char option; 
	int choice, check = 0;
	Check_section(graph, check);
	if (check != 0)
	{
		cout << "\n\n\n\t\tChoose a hobby from where you want to delete a person\n";
		Check_section(graph, check);
		cout << "\n\t\tChoose ---> "; cin >> choice; choice -= 1;
		if (graph->vl[choice].vlisthead->next == NULL)
		{
			cout << "\t\tThe list of hobbies is empty. Try again? Y/N\n";
			cout << "\t\tChoose ---> ";
			cin >> option;
			if (option == 'Y' || option == 'y') { system("cls"); Delete_person(graph); }

		}
		else Deletion(graph, choice);
	}
	else cout << "\n\n\n\t\tAll sections of hobbies are empty."; _getch();
}
void Deletion(Graph *&graph, int &choice)
{
	int Mychoice, counter = 0, pos = 0;
	string Mypos;
	cout << "\n\n\n\t\tChoose the option of deletion a person\n\t\t1) Single deletion\n\t\t2) Multiple deletion\n\n";
	cout << "\n\n\n\t\tChoose ---> "; cin >> Mychoice;
	if (Mychoice == 1)
	{
		node** current = &(graph)->vl[choice].vlisthead; current = &(*current)->next;
		node** prev = &(graph)->vl[choice].vlisthead;
		while ((*current) != NULL)
		{
			cout << "[" << counter + 1 << "] --> " << (*current)->data << "\n";
			current = &(*current)->next;
			counter++;
		}
		cout << "\t\tGive the position ---> "; cin >> pos; pos -= 1;
		if (pos < 0 || pos > counter)
			cout << "\t\tInvalid position\n";
		else
		{
			current = &(*prev)->next;
			for (int i = 0; i < pos; i++)
			{
				current = &(*current)->next;
				prev = &(*prev)->next;
			}
			(*prev)->next = (*current)->next;
		}
	}
	else if (Mychoice == 2)
	{
		node** current = &(graph)->vl[choice].vlisthead; current = &(*current)->next;
		node** prev = &(graph)->vl[choice].vlisthead;
		node** head = prev;
		while ((*current) != NULL)
		{
			current = &(*current)->next;
			counter++;
		}
		cout << "\t\tYou may able to delete only " << counter << " person\n";
		cout << "\t\tGive zero if you want to stop\n"; pos += 1; counter = 1;
		while (pos >= 0 && pos < counter + 1)
		{
			counter = 0; current = &(*head)->next;
			while ((*current) != NULL)
			{
				cout << "[" << counter + 1 << "] --> " << (*current)->data << "\n";
				current = &(*current)->next;
				counter++;
			}
			cout << "\t\tPosition ---> "; cin >> pos; pos -= 1;
			current = &(*head)->next;
			prev = &(*head);
			for (int i = 0; i < pos; i++)
			{
				current = &(*current)->next;
				prev = &(*prev)->next;
			}
			if (pos >= 0)
			{
				(*prev)->next = (*current)->next;
				prev = &(*head);
			}
		}
	}

};

void Delete_section(Graph*& graph, size_t Graphsize)
{
	bool Quit = false;
	string choice;
	int counter = 0;
	int choice_1 = 0;
	if (graph->vl[0].vlisthead != NULL)
	{

		cout << "\n\n\n\t\tChoose the option of deletion\n\n\n\t\t1) Single deletion\n\n\n\t\t2) Multiple deletion\n\n";
		cout << "\t\tChoose ---> "; cin >> choice;
		if (choice == "1")
		{
			cout << "\t\tChoose the section of hobby which you want to delete.\n";
			Display_section(graph);
			cout << "\t\tChoose ---> "; cin >> choice_1; choice_1 -= 1;
			if (choice_1 > Graphsize || choice_1 < 0) { cout << "\t\tInvalid input\n"; _getch(); }
			else {
				free(graph->vl[choice_1].vlisthead);
				Graphsize -= 1;
				Graph* newGraph = CreateGraph(Graphsize);
				newGraph = Recopy(newGraph, graph, choice_1);
				free(graph);
				graph = CreateGraph(Graphsize);
				graph = Copy(newGraph, graph);
				free(newGraph);  _getch();
			}
		}
		else if (choice == "2")
		{
			while (!Quit && graph->vl[0].vlisthead != NULL)
			{
				cout << "\t\tIf you want to stop deletion then push 'zero'\n";
				cout << "\t\tChoose the section of hobby which you want to delete.\n";
				Display_section(graph);
				cout << "\t\tChoose ---> "; cin >> choice_1; choice_1 -= 1;
				if (choice_1 > Graphsize || choice_1 < 0) { cout << "\t\tInvalid input\n"; _getch(); Quit = true; }
				else {
					free(graph->vl[choice_1].vlisthead);
					Graphsize -= 1;
					Graph* newGraph = CreateGraph(Graphsize);
					newGraph = Recopy(newGraph, graph, choice_1);
					free(graph);
					graph = CreateGraph(Graphsize);
					graph = Copy(newGraph, graph);
					free(newGraph);
				}
			}
		}
		else {
			cout << "\n\n\n\t\tInvalid input\n"; _getch(); system("cls"); Delete_section(graph, Graphsize);
		}

	}
	else
	{
		cout << "\n\n\n\t\tThe list of hobby is empty\n"; _getch();
	}
}
void Display_section(Graph*& graph)
{
	for (int i = 0; graph->vl[i].vlisthead != NULL; i++)
	{
		cout  << "\n\n\n     " << i + 1 << ") Section of hobby " << graph->vl[i].vlisthead->data << "\n";
	}cout << "\n";
}

void Display_graph(Graph*& graph)
{
	string choice;
	if (graph->vl[0].vlisthead != NULL)
	{
		for (int i = 0; graph->vl[i].vlisthead != NULL; i++)
		{
			node* cur = graph->vl[i].vlisthead;
			cout << "\n\n\n      " << i + 1 << ") Section of hobby: ";
			cout << cur->data << ":";
			while (cur->next != NULL)
			{
				cur = cur->next;
				cout << cur->data;
				if (cur->next != NULL) cout << "--->";
			}
			cout << endl;
		}
	}
	else cout << "\n\n\n\t\tThe list of hobbies is empty\n"; _getch();
}

void Check_section(Graph*& graph, int &check)
{
	if (check == 0)
	{
		for (int i = 0; graph->vl[i].vlisthead != NULL; i++)
		{
			if (graph->vl[i].vlisthead->next != NULL)
			{
				check++;
			}
		}
	}
	else {
		for (int i = 0; graph->vl[i].vlisthead != NULL; i++)
		{
			if (graph->vl[i].vlisthead->next != NULL)
			{
				cout << "\n\n\n     " << i + 1 << ") Section " << graph->vl[i].vlisthead->data << " : not empty";
			}
			else cout << "\n\n\n     " << i + 1 << ") Section " << graph->vl[i].vlisthead->data << " : is empty";
		}
	}
}
char Menu()
{
	char choice;

	cout << "\n\n\n\t\t\t\tMenu";
	cout << "\n\n\n\t\t\t1) Add a new hobby";
	cout << "\n\n\n\t\t\t2) Delete a hobby";
	cout << "\n\n\n\t\t\t3) Add a person";
	cout << "\n\n\n\t\t\t4) Delete a person";
	cout << "\n\n\n\t\t\t5) Display";
	cout << "\n\n\n\t\t\t6) Quit.\n\n";
	cout << "\t\t\tChoose ---> "; cin >> choice;
	return choice;
}
int main()
{
	size_t Graphsize = 1;
	Graph* graph = CreateGraph(Graphsize);
	char choice;
	do {
		system("cls");
		choice = Menu();
		switch (choice)
		{
		case '1':
			system("cls");
			Create(graph, Graphsize);
				break;
		case '2':
			system("cls");
			Graphsize -= 1;
			Delete_section(graph, Graphsize);
			break;
		case '3':
			system("cls");
			Add_person(graph, Graphsize);
			break;
		case '4':
			system("cls");
			Delete_person(graph);
			break;
		case '5':
			system("cls");
			Display_graph(graph);
			break;
		case '6':
			choice = '6';
			break;
		default: cout << "Invalid input\n";
			break;
		}

	} while (choice != '6');
	return 0;
}

