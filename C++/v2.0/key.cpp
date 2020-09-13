#include<iostream>
#include<windows.h>

using namespace std;
//¼üÅÌ²Ù×÷
class Key_Down_Up {
public:

	int W() {
		keybd_event(87, 0, 0, 0);
		Sleep(200);
		keybd_event(87, 0, KEYEVENTF_KEYUP, 0);
		cout << "W" << endl;
		return 0;
	}
	int S() {
		keybd_event(83, 0, 0, 0);
		Sleep(200);
		keybd_event(83, 0, KEYEVENTF_KEYUP, 0);
		cout << "W" << endl;
		return 0;
	}
	int A() {
		keybd_event(65, 0, 0, 0);
		Sleep(200);
		keybd_event(65, 0, KEYEVENTF_KEYUP, 0);
		cout << "W" << endl;
		return 0;
	}
	int D() {
		keybd_event(68, 0, 0, 0);
		Sleep(200);
		keybd_event(68, 0, KEYEVENTF_KEYUP, 0);
		cout << "W" << endl;
		return 0;
	}
};