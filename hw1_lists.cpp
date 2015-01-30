#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>      
#include <stdlib.h>
#include <string>
#include<sstream>


using namespace std;

//****************************Declares Item*******************************

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

//****************************Concatenate*******************************
Item* concatenate(Item* tail1, Item* tail2) {
	if (tail1->next == NULL){
		tail1->next = tail2;
		
	}
	else{
	concatenate(tail1->next, tail2);
	}
	return tail1;
}	

//****************************Removes Evens*******************************
void removeEvens (Item* tail){
	if (tail == NULL)
	{
		return;
	}
	 if(tail-> next == NULL){
		return;
	}
	int y = tail->next->val; 
	 if (y % 2 ==0)
	{
		tail->next = tail->next->next;
		//cout << " val " << tail->val << " next val " << tail->next->val << "||";
		removeEvens(tail->next);
	}
	else{
		removeEvens(tail->next);
	}
}
//******************************Average Helper*****************************
int aveHelper(Item* tail, int count, int running){
	if (tail->next == NULL){
		return (double)running/count;
	}
	else{
		running= running + tail->next->val;
		count++;
		tail = tail->next; 
		aveHelper(tail, count, running);
	}
}

//****************************Finds Average*******************************
double findAverage(Item* tail){	
	int count = 0;
	int running = tail->val;
	int new_new=0;
	new_new = aveHelper(tail, count, running);
	return new_new;
	

}


		
	

/*****************************************************************************
************************************MAIN************************************
******************************************************************************/
int main(int argc, char* argv[]){
	if(argc < 1){
	    cerr << "Please provide both an input and output file" << endl;
	    return 1;
	  }

	ifstream open_file (argv[1]);
	 if (open_file.fail()){	
		cout << "oops" << endl;	
		return 1;
	}   

//****************************Actually get items from file**********************/

	string rawlist1;			
	string rawlist2;
	string temp;
	getline (open_file, rawlist1);
	getline (open_file, rawlist2);


	stringstream streamy1 (rawlist1);
	stringstream streamy2 (rawlist2);
	
	ofstream ofile (argv[2]);	// makes output file
	
	if (streamy1.rdbuf()->in_avail() == 0){
		ofile << endl;
		ofile << endl;
		ofile << "The average is: 0 " << endl;
		return 1;
	}

//*************************Creates two lists **********************/
int count1 = 0;
int count2 = 0;

	Item* head1;
		head1 = new Item (0, NULL);    // the head element in the list1
	Item* head2;
		head2 = new Item (0, NULL);	// the head element in the list2


Item* prev1 = new Item (0, NULL);
Item* prev2 = new Item (0, NULL);

int xxx;
	while (streamy1 >> xxx){
		if (streamy1.fail()){
			streamy1.clear();
			break;
		}
		//streamy1 >> xxx;
		if (count1 == 0){			
		       	Item* temp1 = new Item (xxx, NULL);		
			count1 = count1+1;
			head1 = temp1;  
			prev1 = temp1;
			}
		else{
			Item* temp1 =  new Item (0, NULL);
			Item* whatever1 = prev1;
			whatever1->next = temp1;
			temp1->val = xxx;
			count1 ++;
			prev1 = temp1;	
		}
		
	}	

	Item* head1c = head1;
	while (head1c != NULL){
		cout << head1c->val <<endl;
		head1c = head1c->next;
	}

int yyy;	
	while (streamy2 >> yyy){
		if (streamy2.fail()){
			streamy2.clear();
			break;
		}
		if (count2 == 0){			
		       	Item* temp2 = new Item (yyy, NULL);		
			count2 = count2+1;
			head2 = temp2;  
			prev2 = temp2;
			}
		else{
			Item* temp2 =  new Item (0, NULL);
			Item* whatever2 = prev2;
			whatever2->next = temp2;
			temp2->val = yyy;
			count2 ++;
			prev2 = temp2;	
		}
		
	}	
	




//****************************Concatenate*******************************
	
	Item* new_list = concatenate(head1, head2); 
	Item* heady = new_list;
	while (!ofile.fail()){	
	ofile << heady->val << " ";	// outputs the list 
		if (heady->next != NULL){	
		heady = heady->next;
		}
		if (heady->next == NULL){
			break;
		}
	}			
	ofile << endl;			

//****************************Remove Evens*******************************
	
	removeEvens (head1);	// remove evens
	while (!ofile.fail()){	
	ofile << head1->val << " ";
	if (head1->next == NULL){
			break;
		}
	head1 = head1->next;		
	}
	ofile << endl;
	 
//****************************Find Average*******************************
	
	double average;
	average = findAverage(new_list);	
	ofile << "The average is " << average; // outputs the average
	ofile.close();	// closes the output document
	

	return 0;
}













