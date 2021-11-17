#pragma once

#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <conio.h>

using namespace std;

class CURSOR {
private:
	FIELD* mine_field;

public:
	int x, y;
	static int number; //現在未使用
	/* コンストラクタ */
	CURSOR(FIELD* _mine_field) : mine_field(_mine_field), x(0), y(0) {}

	/* コピーコンストラクタ */
	CURSOR(const CURSOR& _cursor) : mine_field(_cursor.mine_field), x(_cursor.x), y(_cursor.y) {}

	/* デストラクタ */
	~CURSOR() {
		delete& x, & y;
	}

	/* キーボード操作 */
	inline void key_operation() {
		switch (_getch()) {
		/* 矢印 */
		case 0xe0:
			switch (_getch()) {
			case 0x48: y--; break;
			case 0x50: y++; break;
			case 0x4b: x--; break;
			case 0x4d: x++; break;
			}
			/* clamp */
			x = max(0, min(x, mine_field->get_field_size() - 1));
			y = max(0, min(y, mine_field->get_field_size() - 1));
			break;
		/* Enter */
		case 0x0d:
			/* チェックマークがついていない場合のみ展開可 */
			if (!mine_field->is_check(x, y)) {
				/* 地雷がある場合，すべてを開け，答え表示 */
				if (mine_field->is_mine(x, y)) {
					for (int tmp_y = 0; tmp_y < mine_field->get_field_size(); tmp_y++) {
						for (int tmp_x = 0; tmp_x < mine_field->get_field_size(); tmp_x++) {
							mine_field->set_open(tmp_x, tmp_y, true);
						}
					}
					mine_field->display(*this);
					delete mine_field;
					exit(0);
				}
				/* 地雷がない場合 */
				else {
					mine_field->set_open(x, y, !mine_field->is_mine(x, y));
					/* 周りのマスも探索し，地雷と隣り合っていないマスは開ける */
					mine_field->around_search(x, y);
				}
			}
			break;
		/* Back Space */
		case 0x08:
			/* チェックマークの追加 */
			mine_field->set_check(x, y, !mine_field->is_check(x, y));
			mine_field->check_all_mine();
			break;
		/* Esc */
		case 0x1b:
			delete mine_field;
			exit(0); break;
		}
	}
};

int CURSOR::number = 0;

#endif