#include "../header/field.hpp"
#include "../header/cursor.hpp"

int main() {
	int size;
	cout << "Please enter the size of the field : ";
	cin >> size;
	FIELD mine_field(size);
	CURSOR cursor(&mine_field);
	mine_field.display(cursor);
	
	while (1) {
		cursor.key_operation();
		mine_field.display(cursor);
	}
}