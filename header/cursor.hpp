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
	static int number; //���ݖ��g�p
	/* �R���X�g���N�^ */
	CURSOR(FIELD* _mine_field) : mine_field(_mine_field), x(0), y(0) {}

	/* �R�s�[�R���X�g���N�^ */
	CURSOR(const CURSOR& _cursor) : mine_field(_cursor.mine_field), x(_cursor.x), y(_cursor.y) {}

	/* �f�X�g���N�^ */
	~CURSOR() {
		delete& x, & y;
	}

	/* �L�[�{�[�h���� */
	inline void key_operation() {
		switch (_getch()) {
		/* ��� */
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
			/* �`�F�b�N�}�[�N�����Ă��Ȃ��ꍇ�̂ݓW�J�� */
			if (!mine_field->is_check(x, y)) {
				/* �n��������ꍇ�C���ׂĂ��J���C�����\�� */
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
				/* �n�����Ȃ��ꍇ */
				else {
					mine_field->set_open(x, y, !mine_field->is_mine(x, y));
					/* ����̃}�X���T�����C�n���Ɨׂ荇���Ă��Ȃ��}�X�͊J���� */
					mine_field->around_search(x, y);
				}
			}
			break;
		/* Back Space */
		case 0x08:
			/* �`�F�b�N�}�[�N�̒ǉ� */
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