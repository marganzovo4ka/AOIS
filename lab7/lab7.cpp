#include "AssociativeProcessor.h"

int main()
{
	AssociativeProccessor x;
	x.ShowTable();
	cout << endl << endl << x.GetWord(2);
	cout << endl << endl << x.GetWord(3);
	x.Disparity(x.GetWord(2), x.GetWord(3), 15);
	x.Equivalence(x.GetWord(2), x.GetWord(3), 14);
	x.ProhibSecEl(x.GetWord(2), x.GetWord(3), 13);
	x.ImplFromSecToFirst(x.GetWord(2), x.GetWord(3), 12);
	cout << endl << endl << x.GetWord(12);

	cout << endl << endl;
	x.ShowTable();
	cout << endl << endl << x.GetWord(0);

	x.FindStarting("111");
	cout << endl << endl << x.GetWord(0);
	cout << endl << endl;
	x.ShowTable();
	cout << endl << endl;
	x.Sort();
	x.ShowTable();
	cout << endl << endl << x.GetWord(0);
	cout << endl << endl << x.GetWord(15);

}
