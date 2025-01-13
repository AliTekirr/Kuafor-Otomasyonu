/*Ad Soyad:     Ali Tekir 
  Öðrenci No:   2412729013
  Proje Konusu: Kuaför Otomasyonu 
*/

#include <iomanip> 
#include <string> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>
#include <cstring> 

using namespace std;

struct bilgiler
{
	char ad[100], soyad[100], cinsiyet, telno[10];
};
bilgiler musteri;
int MusteriSayisi=0;

void MusteriEkle();
void MusteriListele();
void MusteriAra();
void MusteriSil();
void MusteriDuzenle();

int main() 
{
	setlocale(LC_ALL, "TURKISH");
	/*Bu bölüm kullanýcýyý karþýlayacak olan menü bölümüdür. Buradan kullanýcý yapmak 
	istediði iþlemi seçip ilgili iþlemi yapacak olan fonksiyona yönlendirilecek.*/
	char donus,secim;
	do
	{
	system("cls");		
	cout << "\t==================================" << endl;
    cout << "\t|       Hoþgeldiniz              |" << endl;
    cout << "\t==================================" << endl;
    cout << "\t|       Seçim Yapýnýz           |" << endl;
    cout << "\t----------------------------------" << endl;
    cout << "\t|  1 - Müsteri Ekleme            |" << endl;
    cout << "\t|  2 - Müsteri Listeleme         |" << endl;
    cout << "\t|  3 - Müsteri Arama             |" << endl;
    cout << "\t|  4 - Müsteri Sil               |" << endl;
    cout << "\t|  5 - Müsteri Düzenle           |" << endl;
    cout << "\t----------------------------------" << endl;
    cout << "\nSeçiminizi giriniz(1, 2, 3, 4 veya 5): ";
    cin >> secim;
	
	switch(secim) 
	{
		case '1' : 
		{
		MusteriEkle();
		break;	
		}
		case '2' : 
		{
		MusteriListele();
		break;
		}
		case '3' : 
		{
		MusteriAra();
		break;
		}
		case '4' : 
		{
		MusteriSil();
		break;
		}
		case '5' : 
		{
		MusteriDuzenle();
		break;
		}
		default:
		{ 
		cout<<"Hatalý seçim yaptýnýz tekrar denemek için herhangi bir tuþa basýnýz.\n";
		system("Pause");
		return main();
		}
	}
	cout << "\nAnamenüye Dönmek icin: a basýnýz çýkmak için: s basýnýz " <<endl ; 
	donus=getche();
	cout<<endl;
	
	}while(donus=='a'); 
		
	system("Pause");
	return 0;
}

void MusteriEkle() //Müþterilerin musteri.dat'a kaydedileceði fonksiyon
{
	ofstream yazbilgiler("musteri.dat",ios::binary|ios::app);
	char kontrol;
	do
	{
		cout<<"Müþterinin ismini giriniz: ";
		cin>>musteri.ad;
		cout<<"Müþterinin soyadýnýz giriniz: ";
		cin>>musteri.soyad;
		do
		{
		cout<<"Müþterinin cinsiyetinin seçiniz(E/K): ";
		musteri.cinsiyet=getch();
		if(musteri.cinsiyet=='E'||musteri.cinsiyet=='e'||musteri.cinsiyet=='K'||musteri.cinsiyet=='k')
		{
			break;
		}
			else
				{
				cout<<"\nHatalý giriþ yaptýnýz tekrar deneyiniz!\n";
			    }
		}while(true);	
		cout<<"\nMüþterinin telefon numarasýný giriniz(baþýnda 0 olmadan): ";
		cin>>musteri.telno;
	
		yazbilgiler.write(reinterpret_cast<char*>(&musteri), sizeof(musteri));
		MusteriSayisi++;
		cout << "Baþka müþteri eklemek ister misiniz (E/H): ";
		kontrol=getche();
		cout << endl;
	}while(kontrol=='e' || kontrol=='E');
	
	cout<<"Müþteri baþarýyla eklendi"<<endl;
	
	yazbilgiler.close();
}

void MusteriListele() //Müþterilerin musteri.dat'tan alýnýp listeleneceði fonksiyon
{
	
	
	ifstream okubilgiler("musteri.dat",ios::binary|ios::app);
	okubilgiler.seekg(0, ios::end);
	int MusteriSayisi = okubilgiler.tellg() / sizeof(musteri);
	cout<< MusteriSayisi<<" Adet müþteri bulunmakta\n";
	
	if(MusteriSayisi>0)
	{		
		for(int i=0; i<MusteriSayisi;i++)
		{
			cout<<endl<<i+1<<". Müþteri"<<endl;
			okubilgiler.seekg(i*sizeof(musteri));
			okubilgiler.read(reinterpret_cast<char*>(&musteri),sizeof(musteri));
			cout<<endl;
			cout<<"Adý: "<<musteri.ad;
			cout<<"\nSoyadý: "<<musteri.soyad;
			cout<<"\nCinsiyeti: ";
			if(musteri.cinsiyet=='E'||musteri.cinsiyet=='e') //Ekrana çýktý olarak E/K yazdýrmak yerine Erkek/Bayan yazdýrmak için burada ifelse kullandým
				cout<<"Erkek";
			else
				cout<<"Bayan";
			cout<<"\nTelefon Numarasý: "<<musteri.telno<<endl;
		}
		
	}
	else
	{
		cout<<"\nKayýt bulunamadý!"<<endl;
	}
	okubilgiler.close();
}

void MusteriAra()//Müþterilerin musteri.dat'ta musteri bilgilerinin aranacaðý fonksiyon
{
	char musteri_isim[100];
	bool var;
	ifstream aramusteri("musteri.dat",ios::binary|ios::app);
	aramusteri.seekg(0, ios::end);
	int MusteriSayisi = aramusteri.tellg() / sizeof(musteri);
	cout<<"Bulmak istediðiniz müþterinin adýný giriniz: ";
	cin>>musteri_isim;
	
	if (MusteriSayisi > 0)
	{
	
		
		for(int i=0; i<MusteriSayisi;i++)
		{
			aramusteri.seekg(i*sizeof(musteri));
			aramusteri.read(reinterpret_cast<char*>(&musteri),sizeof(musteri));
			if(strcmp(musteri.ad,musteri_isim)==0)
			{
				cout<<endl<<i+1<<". Kayýtta bulundu"<<endl;
				cout<<"Adý: "<<musteri.ad;
				cout<<"\nSoyadý: "<<musteri.soyad;
				cout<<"\nCinsiyeti: ";
				if(musteri.cinsiyet=='E'||musteri.cinsiyet=='e')
					cout<<"Erkek";
				else
					cout<<"Bayan";
				cout<<"\nTelefon Numarasý: "<<musteri.telno<<endl;
			}
			
		}
	}
	else
	cout << "Sistemde kayýt bulunamadý..." << endl;
	
	aramusteri.close();
}

void MusteriSil()//Müþterilerin musteri.dat'ta musteri bilgilerinin silineceði fonksiyon
{
    char telno[80];
    char secim = ' ';
    bool var = false;
    
    ifstream musterisil("musteri.dat", ios::binary);
    musterisil.seekg(0, ios::end);
    int MusteriSayisi = musterisil.tellg() / sizeof(musteri);

    cout << "Kaydý silinecek müþterinin telefon numarasýný giriniz: ";
    cin >> telno;

    

    for (int i = 0; i < MusteriSayisi; i++) 
	{
		musterisil.seekg(i*sizeof(musteri));
        musterisil.read(reinterpret_cast<char*>(&musteri), sizeof(musteri));

        if (strcmp(musteri.telno, telno) == 0) 
		{
            cout<<endl<<i+1<<". Kayýtta bulundu"<<endl;
			cout<<"Adý: "<<musteri.ad;
			cout<<"\nSoyadý: "<<musteri.soyad;
			cout<<"\nCinsiyeti: ";
			if(musteri.cinsiyet=='E'||musteri.cinsiyet=='e')
				cout<<"Erkek";
			else
				cout<<"Bayan";
			cout<<"\nTelefon numarasý: "<<musteri.telno<<endl;
            cout << "\n\nSilmek istediðiniz kayýt bu mu:  [E/H]: ";
            secim = getche();
            
            if(secim == 'H' || secim == 'h')
            {      
			    bilgiler ymusteri;
                ofstream yedek("Yedek.dat", ios::binary | ios::app);
                
                strcpy(ymusteri.ad,musteri.ad);
                strcpy(ymusteri.soyad,musteri.soyad);
                strcpy(ymusteri.telno,musteri.telno);
                musteri.cinsiyet=ymusteri.cinsiyet;
                        
            	yedek.write((char*)&musteri, sizeof(musteri));
                yedek.close();
            }
            if(secim=='e'||secim=='E')
            {
   				var=true;
  		 	}
		}
		else
		{
			bilgiler ymusteri;
            ofstream yedek("Yedek.dat", ios::binary | ios::app);
                
        	strcpy(ymusteri.ad,musteri.ad);
            strcpy(ymusteri.soyad,musteri.soyad);
            strcpy(ymusteri.telno,musteri.telno);
            musteri.cinsiyet=ymusteri.cinsiyet;
                        
            yedek.write((char*)&musteri, sizeof(musteri));
			yedek.close();
		}
		
    }
    musterisil.close();
    if(var)
    {
        remove("musteri.dat");
        rename("Yedek.dat","musteri.dat");
        cout<<"\n Kayýt baþarýyla silindi"<<endl;
    }
    else
    {
    	remove("Yedek.dat");
        cout<<"\n Kayýt bulunamadý"<<endl;                  
    }
}

void MusteriDuzenle()//Müþterilerin musteri.dat'ta musteri bilgilerinin güncelleneceði fonksiyon
{
    char telno[80];
    char secim = ' ';
    bool var = false;

    ifstream musteriguncelle("musteri.dat", ios::binary);

    musteriguncelle.seekg(0, ios::end);
    int MusteriSayisi = musteriguncelle.tellg() / sizeof(musteri);

    cout << "Kaydý güncellemek istediðiniz müþterinin telefon numarasýný giriniz: ";
    cin >> telno;

    ofstream yedek("Yedek.dat", ios::binary);

    for (int i = 0; i < MusteriSayisi; i++) 
	{
        musteriguncelle.read(reinterpret_cast<char*>(&musteri), sizeof(musteri));

        if (strcmp(musteri.telno, telno) == 0) 
		{
            cout << "\nKaydý bulundu: " << endl;
            cout << "Adý: " << musteri.ad;
			cout<< "\nSoyadý: " << musteri.soyad;
			cout<<"\nCinsiyeti: ";
			if(musteri.cinsiyet=='E'||musteri.cinsiyet=='e')
				cout<<"Erkek";
			else
				cout<<"Bayan";
            cout<< "\nTelefon numarasý: " << musteri.telno << endl;

            cout << "\nBu kaydý güncellemek istiyor musunuz: [E/H]: ";
            secim = getche();

            if (secim == 'E' || secim == 'e') 
			{
                cout << "\nYeni bilgileri giriniz:\n";
                cout << "Müþterinin ismini giriniz: ";
                cin >> musteri.ad;
                cout << "Müþterinin soyadýný giriniz: ";
                cin >> musteri.soyad;

                do 
				{
                    cout << "Müþterinin cinsiyetini seçiniz (E/K): ";
                    cin >> musteri.cinsiyet;
                    if (musteri.cinsiyet == 'E' || musteri.cinsiyet == 'e' || musteri.cinsiyet == 'K' || musteri.cinsiyet == 'k') 
					{
                    	break;
                    }
					else 
					{
                        cout << "Hatalý giriþ yaptýnýz, tekrar deneyiniz!\n";
                    }
                }while (true);

                cout << "Müþterinin telefon numarasýný giriniz: ";
                cin >> musteri.telno;

                yedek.write(reinterpret_cast<char*>(&musteri), sizeof(musteri));
                var = true;
            } 
        }
		else 
		{
            yedek.write(reinterpret_cast<char*>(&musteri), sizeof(musteri));
        }
    }

    musteriguncelle.close();
    yedek.close();

    if (var) 
	{
        if (remove("musteri.dat") == 0) 
		{
            if (rename("Yedek.dat", "musteri.dat") == 0) 
			{
                cout << "\nMüþteri baþarýyla güncellendi." << endl;
            }
        }
    }
	else 
	{
        remove("Yedek.dat");
        cout << "\nKayýt bulunamadý." << endl;
    }
}

