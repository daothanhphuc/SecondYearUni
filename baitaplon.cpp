// Hệ thống quản lý nhân sự --> kế toán: 

// Phúc
// 1. Thông tin nhân sự (infor): class include : tên, tuổi, giới tính, địa chỉ, vị trí công việc, mức lương
// --> create function about Add, Insert, Delete, Search infor 
// --> Sử dụng LinkedList thì sẽ cần phân loại các nhóm nhân sự : quản lý bộ phận, hỗ trợ kĩ thuật, nhân sự còn lại

// Ngân
// 2. Tính toán lương và phúc lợi: --> phải có các hàm tính lương thưởng/phạt
// --> Hàm lương trợ cấp / phụ cấp
// --> Hàm tính khoản phúc lợi
// --> Hàm tính lương làm việc theo giờ chính 
// --> Hàm tính lương BONUS ( thưởng ngày lễ, thưởng làm thêm giờ-tùy dịp) : ngày lễ tết + 1 triệu, làm thêm giờ 
//     và với nhân viên marketing --> thưởng theo số lượng hợp đồng kí đc theo tháng với các mốc là 5 - 10 - 15:
//     1.000.000 VND cho mỗi hợp đồng từ 1-5, 1.500.000 VND cho mỗi hợp đồng từ 6-10, và 2.500.000 VND cho mỗi hợp đồng từ 11-15.
// --> Hàm phạt ( nghỉ ngoài ngày phép - làm ko đủ giờ/ngày --> trừ thẳng vào số ngày làm việc thực tế )
// ==> SUM = (lương chính + phụ cấp, trợ cấp)/26 *số ngày làm việc thực tế + thưởng

// Mai Linh
// 4. Phân quyền và truy cập: --> quản lý thì được add nhân viên còn nhân viên chỉ được quyền xem thông tin của mình,...
// a) Xác định vai trò của đối tượng:
// b) Xác thực danh tính đối tượng --> password including special characters and numbers
// c) Gán quyền cho đối tượng: 
// d) Thực hiện quyền theo yêu cầu của người dùng:  
// e) Lưu lại lịch sử truy cập: 

// Quân
// 3. Thống kê và báo cáo về thông tin - số lượng nhân sự theo vị trí, dự án,...
// 5. Điểm danh nhân viên:  
// void recordAttendanceStartTime() {
//     // Get current time
//     time_t rawTime;
//     struct tm* startTime;
//     time(&rawTime);
//     startTime = localtime(&rawTime);
//     // Output the start time
//     cout << "Attendance Start Time: " << asctime(startTime);
// }
// 6. Giao diện người dùng trực tiếp trên console:
#include<iostream>
// #include<set>
#include<algorithm>
#include<string>
#include<ctime>
#include<map>
#include<iomanip>
using namespace std;
struct Personnel {
    string name;
    int tuoi;
    string gender;
    string address;
    string job;
    int ngaycong;
    int bacluong;
    double TNCT; // tham nien cong tac
    string password;
	time_t startTime; // Thêm trường startTime để lưu thời gian bắt đầu làm việc
}; 
struct Node {
    Personnel p;
    Node *next;
};
typedef Node *Manager;
typedef Node *ITSupport;
typedef Node *OtherPosition;
void InitList (Node* &H) {
	H = NULL;
}
bool IsEmpty (Node* H) {
	return (H == NULL);
}
void InsertBegin (Node* &H, Personnel x) {
	Node *staff = new Node;
	staff->p = x;
	staff->next = NULL;
	if (IsEmpty(H) ) H = staff; //cap nhat con tro dau linkedlist
	else {
		staff->next = H;
		H = staff;              //cap nhat con tro dau linkedlist
	}
}
Node* InsertAfter ( Node* &H, Node* P, Personnel x) {
	Node* staff = new Node;
	staff->p = x ;
	staff->next = NULL;
	if (IsEmpty(H) ) return NULL;
	else {
		if ( P == NULL ) return NULL;
		staff->next = P->next;
		P->next = staff;
	}
	return staff;
}
Node* InsertBefore ( Node* &H, Node* P, Personnel x) {
	Node* staff = new Node;
	staff->p = x ;
	staff->next = NULL;
	if ( IsEmpty(H) ) return NULL;
	else {
		if ( P == NULL) return NULL;
		staff->p = P->p;
		P->p = x;
		staff->next = P->next;
		P->next = staff;
	}
	return staff;
}
void Delete ( Node* &H) {		// delete first unit
	if ( IsEmpty(H) ) cout << "Empty" << endl;
	else {
		Node* staff = H;
		H = H->next;
		delete staff;
	}
}
void DeletePersonnel (Node* &H, string name) {
    Node* P = H;
    while ( P->p.name != name ) P = P->next;
	if ( H == NULL || P == NULL) cout << "No data match this name" << endl;
	if ( H == P && P->next == NULL) {	// List have only 1 unit 
		H = NULL;
		delete P;
	}
	else {
		Node* R = H;				// take steps to delete the chosen Node (P)
		while ( R->next != P ) R = R->next;
		R->next = P->next;
		delete P;
	}						
}
void GetP ( Node* H, string name) {
	int count = 0;
	Node* staff = H;
	while ( staff != NULL) {
		if ( staff->p.name == name) {
            count++;
			cout << "--> Got data of staff: " << endl;
            cout << "Name: " << staff->p.name << endl;
            cout << "Gender: " << staff->p.gender << endl;
            cout << "Position:"<< staff->p.job << endl;
            cout << "Address: "<< staff->p.address << endl;
        }
		staff = staff->next;
	}
    if (count == 0) cout << "Can not find this person" << endl;
}
void display (Node* H) {
	Node* staff = H;
	while ( staff != NULL) {
		cout << staff->p.name << endl;
		staff = staff->next;
	}
}
string CutFirstName(const string &name) {
    string firstName;
    size_t lastSpacePos = name.rfind(' '); // Find the last space character
    //  ' ' is a non negative integer --> have to use data type size_t to store
    if (lastSpacePos != string::npos) {               // the use of string::npos --> means not found 
        firstName = name.substr(lastSpacePos + 1); // Extract the substring after the last space
    } else {
        //there is no space
        firstName = name;
    }
    return firstName;   
}
string CutSecondName ( const string &name) {
    string secondWord;
    size_t firstSpacePos = name.find(' '); 
    if (firstSpacePos != string::npos) {
        size_t secondSpacePos = name.find(' ', firstSpacePos + 1); // Find the second space character
        if (secondSpacePos != string::npos) {
            secondWord = name.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1); // Extract the substring between the first and second space
        } else {
            //there is no second space
            secondWord = name.substr(firstSpacePos + 1);
        }
    } else {
        //there is no space
        secondWord = name;
    }
    return secondWord;
}
string CutThirdName (const string &name) {
    string thirdWord;
    size_t firstSpacePos = name.find(' '); 
    if (firstSpacePos != string::npos) {
        size_t secondSpacePos = name.find(' ', firstSpacePos + 1);  
        size_t thirdSpacePos  = name.find(' ', secondSpacePos + 1 );// Find the third one
        if (thirdSpacePos != string::npos) {
            thirdWord = name.substr(secondSpacePos + 1, thirdSpacePos - secondSpacePos - 1); // Extract the substring between the first and second space
        } else {
            //there is no third space
            thirdWord = name.substr(secondSpacePos + 1);
        }
    } else {
        //there is no space
        thirdWord = name;
    }
    return thirdWord;
}
string CutLastName ( const string &name) {
    string lastWord;
    size_t firstSpacePos = name.find(' ');
    if ( firstSpacePos != string::npos ) {
        lastWord = name.substr(0, firstSpacePos );
    } else {
        lastWord = name;
    }
    return lastWord;
}
void CompareAndInsert(Node* &H, Node* &P, Personnel x, string lastWord, string pivot) {
    int minLength = min(lastWord.length(), pivot.length());
    for (int j = 0; j < minLength; j++) {
        if (lastWord[j] > pivot[j]) {
            P = InsertAfter(H, P, x);
            return;
        } else if (lastWord[j] < pivot[j]) {
            P = InsertBefore(H, P, x);
            return;
        }
        if (j == minLength - 1) {
            if (lastWord.length() == minLength) {
                P = InsertBefore(H, P, x);
                return;
            } else if (pivot.length() == minLength) {
                P = InsertAfter(H, P, x);
                return;
            }
        }
    }
}
void InsertNode(Node* &H, Personnel x) {
    Node* P = H;
    Node* staff = new Node;
    staff->p = x;
    staff->next = NULL;
    int spaceCount = count(x.name.begin(), x.name.end(), ' ');
    if (IsEmpty(H)) {
        H = staff;
        return;
    }
    string a;
    string b;
    if (spaceCount == 2) {
        a = CutFirstName(x.name);
        b = CutFirstName(P->p.name);
    } else if (spaceCount == 3) {
        a = CutFirstName(x.name);
        b = CutFirstName(P->p.name);
    } else {
        // only accept string type name with no more than 3 space ' '
        cout << "Invalid name" << endl;
        return;
    }

    while (a[0] - b[0] > 0 && P->next != NULL) {
        P = P->next;
        b = CutFirstName(P->p.name);
    }

    if (a != b) {
        CompareAndInsert(H, P, x, a, b);
    }
    else if ( a == b ) {
        a = CutSecondName(x.name);
        b = CutSecondName(P->p.name);
        if ( a == b ) {
            if ( spaceCount == 2 ) {
                a = CutLastName(x.name);
                b = CutLastName(P->p.name);
                CompareAndInsert(H, P, x, a, b);
            }
            else if ( spaceCount == 3 ) { 
                a = CutThirdName(x.name);
                b = CutThirdName(P->p.name); 
                if ( a == b) { // ten dem thu 2 same
                    a = CutLastName(x.name);
                    b = CutLastName(P->p.name); 
                    CompareAndInsert(H, P, x, a, b);    
                }
                else {          
                    CompareAndInsert(H, P, x, a, b);  
                }
            }
        }
        else { // ten dem thu nhat khac nhau
            CompareAndInsert(H, P, x, a, b);  
        }
    }
}
void createPersonnel(Personnel &p) {
    cout << "-Name: ";
    getline(cin, p.name);
    
    cout << "- Age: ";
    cin >> p.tuoi;
    cin.ignore(); // Đọc kí tự '\n' trong bộ nhớ đệm
    cout << "-Gender: ";
    getline(cin, p.gender); 
    cout << "-Address: ";
    getline(cin, p.address);
    cout << "- Position: ";
    getline(cin, p.job);
    // cout << "Nhap so ngay lam viec trong thang: ";
    // cin >> p.ngaycong;
    // cin.ignore(); 
    cout << "- Password (including at least 1 special character and a number): ";
    getline(cin, p.password);
}
Node* SearchPersonnel ( Node* &H){
	Personnel a;
	cout<< "Nhap ten nhan vien: ";    // co nen thay bang ma so nhan vien? 
	cin >> a.name;
	Node* P = H;
	if(IsEmpty(H)) return NULL;
	while(P!=NULL) {
		if(P->p.name==a.name) return P;
		P=P->next;
	}
	return NULL;
}
// ham tinh luong
double Salary( Node* &H){
	Node* Q = SearchPersonnel(H);
	double tongluong;
	// luong chinh lam viec
	double luongchinh;
	// tinh Phu cap hang thang ( gom: Phu cap trach nhiem; phu cap lao dong chinh thuc)
	double PC, PCTN, PCLD;
	// luong & phu cap theo tung chuc vu
	if(Q->p.job=="Giam doc") {
		PCTN = 3000000;
		PCLD = 1500000 + 1000000 + 500000; // tien an & tien dien thoai & tien xang xe 
		switch(Q->p.bacluong){
			case 1: luongchinh = 15000000; break;
			case 2: luongchinh = 15750000; break;
			case 3: luongchinh = 16540000; break;
			case 4: luongchinh = 17370000; break;
			case 5: luongchinh = 18240000; break;
			case 6: luongchinh = 19160000; break;
			case 7: luongchinh = 20120000; break; 
		}  
	} 
	else if (Q->p.job=="Pho giam doc") {
		PCTN = 2000000;
		PCLD = 1300000 + 800000 + 400000;
		switch(Q->p.bacluong){
			case 1: luongchinh = 12000000; break;
			case 2: luongchinh = 12600000; break;
			case 3: luongchinh = 13230000; break;
			case 4: luongchinh = 13900000; break;
			case 5: luongchinh = 14600000; break;
			case 6: luongchinh = 15330000; break;
			case 7: luongchinh = 16100000; break; 
		}
	}
	else if (Q->p.job=="Ke toan truong") {
		PCTN = 1000000;
		PCLD = 1200000 + 600000 + 300000;
		switch(Q->p.bacluong){
			case 1: luongchinh = 10000000; break;
			case 2: luongchinh = 10500000; break;
			case 3: luongchinh = 11030000; break;
			case 4: luongchinh = 11590000; break;
			case 5: luongchinh = 12170000; break;
			case 6: luongchinh = 12780000; break;
			case 7: luongchinh = 13420000; break; 
		}
	}
	else if (Q->p.job=="Truong phong kinh doanh") { 
		PCTN = 1500000;
		PCLD = 1200000 + 800000 + 800000;
		switch(Q->p.bacluong){
			case 1: luongchinh = 11000000; break;
			case 2: luongchinh = 11750000; break;
			case 3: luongchinh = 12540000; break;
			case 4: luongchinh = 13000000; break;
			case 5: luongchinh = 13100000; break;
			case 6: luongchinh = 13750000; break;
			case 7: luongchinh = 14050000; break; 
		}
	}
	else if (Q->p.job=="Nhan vien ke toan"){
		PCLD = 1000000 + 300000 + 300000;
		switch(Q->p.bacluong){
			case 1: luongchinh = 7000000; break;
			case 2: luongchinh = 7350000; break;
			case 3: luongchinh = 7720000; break;
			case 4: luongchinh = 8110000; break;
			case 5: luongchinh = 8520000; break;
			case 6: luongchinh = 8950000; break;
			case 7: luongchinh = 9400000; break; 
		}
	}
	else if (Q->p.job=="Nhan vien kinh doanh"){
		PCLD = 1000000 + 300000 + 300000;
		switch(Q->p.bacluong){
			case 1: luongchinh = 6500000; break;
			case 2: luongchinh = 6830000; break;
			case 3: luongchinh = 7180000; break;
			case 4: luongchinh = 7540000; break;
			case 5: luongchinh = 7920000; break;
			case 6: luongchinh = 8320000; break;
			case 7: luongchinh = 8740000; break; 
		}
	}
	else if (Q->p.job=="Nhan vien van phong"){
		PCLD = 1000000 + 300000; // an trua & xang xe
		switch(Q->p.bacluong){
			case 1: luongchinh = 6000000; break;
			case 2: luongchinh = 6300000; break;
			case 3: luongchinh = 6620000; break;
			case 4: luongchinh = 6960000; break;
			case 5: luongchinh = 7310000; break;
			case 6: luongchinh = 7680000; break;
			case 7: luongchinh = 8070000; break; 
		}
	}
	else if (Q->p.job=="Nhan vien tap vu"){
		PCLD = 1000000 + 300000; // an trua & xang xe
		switch(Q->p.bacluong){
			case 1: luongchinh = 5000000; break;
			case 2: luongchinh = 5250000; break;
			case 3: luongchinh = 5520000; break;
			case 4: luongchinh = 5800000; break;
			case 5: luongchinh = 6090000; break;
			case 6: luongchinh = 6400000; break;
			case 7: luongchinh = 6720000; break; 
		}
	}
	PC = PCTN + PCLD;
	cout<< "Luong phu cap: " << setprecision(2)<< fixed << PC << endl;
	cout<< "Luong chinh: " <<setprecision(2) << fixed <<  luongchinh << endl;
	
	// luong lam viec them gio ( gom: luong lam them vao ngay thuong; CN; Le/tet)
	int NT, CN, LT;
	double LVTG; // luong lam viec them gio
	cout << "Nhap so gio lam them vao ngay thuong: "; cin>> NT;
	cout << "Nhap so gio lam them vao chu nhat: "; cin>> CN;
	cout << "Nhap so gio lam them vao Le/tet: "; cin>> LT;
	LVTG = ( NT*1.5 + CN*2 + LT*3 )*25000; // tien luong theo gio = 25000 VND / h
	cout << "Luong lam viec them gio: " << LVTG << endl;
	
	// thuong ( gom: thuong tham nien cong tac > 3 nam, thuong dat doanh thu, thuong ngay le)
	double Thuong, tTNCT, tDT, tNL;
	if(Q->p.TNCT >= 3){
		cout << "Nhap thuong tham nien cong tac ";  // thuong tham nien cong tac se duoc cong bo vao thang cuoi cua nam
		cin >> tTNCT;
	}
	cout << "Nhap thuong doanh thu "; cin>> tDT;
	cout << "Nhap thuong ngay le "; cin >> tNL;
	Thuong = tTNCT + tDT + tNL;
	cout << "Luong thuong: " << Thuong << endl;
	
	//Phat ( ly do: ...)
	string Note; 
	double Phat; 
	cout << "Nhap so luong bi tru "; cin>> Phat;
	if(Phat!=0) cout <<  "Ly do tru: "; getline(cin,Note); cin.ignore(); 
	
	tongluong = (luongchinh + PC)/26 *Q->p.ngaycong + Thuong - Phat;
	cout << "Tong luong: " <<setprecision(2) << fixed <<  tongluong << endl; 
} 
// Hàm thống kê và hiển thị thông tin nhân viên theo vị trí công việc
void countPositions( Node* &list) {
    map<string, int> positionCount;
    Node* temp = list;
    while (temp != NULL) {
        positionCount[temp->p.job]++;
        temp = temp->next;
    }
    cout << "Thong tin nhan vien theo vi tri cong viec:\n";
    for (const auto& pair : positionCount) {
        cout << "Vi tri: " << pair.first << ", So luong nhan vien: " << pair.second << endl;
    }
}
// Hàm điểm danh cho tất cả nhân viên trong danh sách
void markAttendanceForAll(LinkedList& list) {
    Node* temp = list;
    while (temp != NULL) {
        time_t currentTime;
        time(&currentTime);
        double diffTime = difftime(currentTime, temp->p.startTime);
        int ngayLamViec = diffTime / (60 * 60 * 24); // Số giây trong một ngày làm việc

        // Nếu là một ngày mới, thêm một Node mới vào danh sách
        if (ngayLamViec >= 1) {
            Personnel newEmployee = temp->p; // Sao chép thông tin từ nhân viên hiện tại
            newEmployee.startTime = currentTime; // Cập nhật thời gian bắt đầu mới
            addEmployee(list, newEmployee); // Thêm nhân viên mới vào danh sách
        }

        temp = temp->next;
    }
}
int main() {
    Personnel p1= {"Dao Thanh Phuc", 20,"Male","Ha Noi","BE"};
	Personnel p2= {"Bui Duc Quan", 20,"Male","Nghe An","FE"};
	Personnel p3= {"Nguyen Phuong Anh", 22,"Female","Nghe An","Manager"};
    Personnel p4= {"Nguyen Van Minh", 22,"Female","Lao Cai","Manager"};
    Personnel p5= {"Le Trong Phu", 20,"Male","Ha Noi","BE"};
    Personnel p6= {"Bui Trung Phu", 20,"Male","Nghe An","FE"};
    Personnel p7= {"Nguyen Thi Kim Ngan", 20, "Female", "Thai Binh","Manager"};
    Personnel p9= {"Dao Thi Hong Minh", 20, "Female", "Thai Binh","Manager"};
    Personnel p10= {"Dao Nguyen Hong Minh", 20, "Female", "Thai Binh","Manager"};
    Personnel p8= {"Nguyen Kim Ngan", 20, "Female", "Thai Binh","Manager"};
    // createPersonnel(p7);

	OtherPosition O;
	InitList(O);
	InsertNode(O,p2);
	InsertNode(O,p1);
	InsertNode(O,p3);
    InsertNode(O,p4);
    InsertNode(O,p5);
    InsertNode(O,p6);
    InsertNode(O,p7);
    InsertNode(O,p8);
    InsertNode(O,p9);
    InsertNode(O,p10);

	countPositions(O);
    
	display(O);
    
    // GetP(O,"Dao Thanh Phuc");
    return 0;
}

