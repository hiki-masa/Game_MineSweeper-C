#pragma once

#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <vector>

#include "random.hpp"

using namespace std;

/* マスごとの設定 */
class MINE {
public:
	/* 対象のマスを開けられたかの判定 */
	bool open;
	/* 対象のマスの地雷の有無 */
	bool mine;
	/* チェックの有無 */
	bool check;

	/* コンストラクタ */
	MINE() : open(false), mine(false), check(false) {}
};

class FIELD {
private:
	int field_size;
	vector<vector<MINE>> field;

public:
	/* コンストラクタ */
	FIELD(int _field_size) : field_size(_field_size) {
		/* マスの初期化 */
		field.resize(field_size);
		for (int i = 0; i < field_size; i++) {
			field[i].resize(field_size);
		}
		/* 地雷の設置 */
		int mine_number = 0, tmp_x, tmp_y;
		while (mine_number < field_size * field_size / 10) {
			tmp_x = (rnd() - 1e-6) * field_size, tmp_y = (rnd() - 1e-6) * field_size;
			if (field[tmp_x][tmp_y].mine == false){
				mine_number++;
				field[tmp_x][tmp_y].mine = true;
			}
		}
	}

	/* デストラクタ */
	~FIELD() {
		delete &field_size;
		delete &field;
	}

	/* セッタ― */
	void set_open(int _x, int _y, bool open_status) {
		field[_x][_y].open = open_status;
	}
	void set_mine(int _x, int _y, bool mine_status) {
		field[_x][_y].open = mine_status;
	}
	void set_check(int _x, int _y, bool check_status) {
		field[_x][_y].check = check_status;
	}
	/* ゲッター */
	int get_field_size() const {
		return field_size;
	}
	bool is_open(int _x, int _y) const {
		return field[_x][_y].open;
	}
	bool is_mine(int _x, int _y) const {
		return field[_x][_y].mine;
	}
	bool is_check(int _x, int _y) const {
		return field[_x][_y].check;
	}

	/* 表示 */
	template <class T> void display(T cursor) {
		system("cls");
		for (int y = 0; y < field_size; y++) {
			for (int x = 0; x < field_size; x++) {
				/* カーソル表示 */
				if (x == cursor.x && y == cursor.y) cout << "↓";
				/* 開けたマスの表示 */
				else if (field[x][y].open) {
					/* 地雷マス */
					if (field[x][y].mine) cout << "◆";
					/* 空白マス */
					else cout << " " << around_mine_count(x, y);
				}
				/* チェックマスの表示 */
				else if (field[x][y].check) {
					cout << "×";
				}
				/* 開けてないマスの表示 */
				else cout << "■";
			}
			cout << endl;
		}
	}

	/* 地雷をすべて見つけたかの判定 */
	void check_all_mine() const {
		for (int y = 0; y <= field_size - 1; y++) {
			for (int x = 0; x <= field_size - 1; x++) {
				if ((field[x][y].mine == true and field[x][y].check != true) or (field[x][y].mine != true and field[x][y].check == true)){
					return;
				}
			}
		}
		cout << "Game Clear!!" << endl;
		delete this;
		exit(0);
	}

	/* 周りの地雷の数のカウント */
	int around_mine_count(int _x, int _y) {
		int count = 0;
		for (int y = max(0, _y - 1); y <= min(_y + 1, field_size - 1); y++) {
			for (int x = max(0, _x - 1); x <= min(_x + 1, field_size - 1); x++) {
				if (field[x][y].mine == true) count++;
			}
		}
		return count;
	}
	void around_search(int _x, int _y) {
		for (int y = max(0, _y - 1); y <= min(_y + 1, field_size-1); y++) {
			for (int x = max(0, _x - 1); x <= min(_x + 1, field_size-1); x++) {
				/* 周りの地雷数が0個のマスの場合，マスを展開 */
				if (around_mine_count(x, y) == 0 && field[x][y].open == false) {
					/*  */
					for (int y1 = max(0, y - 1); y1 <= min(y + 1, field_size - 1); y1++) {
						for (int x1 = max(0, x - 1); x1 <= min(x + 1, field_size - 1); x1++) {
							/*  */
							if (field[x1][y1].open == false) {
								set_open(x1, y1, true);
								around_search(x1, y1);
							}
						}
					}
				}
			}
		}
	}
};

#endif
