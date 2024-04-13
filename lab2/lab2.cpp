#include "TruthTable.h"

int main()
{
	TruthTable table("a ~ !a");
	table.Calculate();
	table.Print();
	cout << endl << table.SDNF() << endl << table.SKNF() << endl << table.NumericForm() << endl << table.IndexForm();
}