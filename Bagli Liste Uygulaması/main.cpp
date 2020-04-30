#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <regex>
#include <cstdio>

using namespace std;

class Koltuk {

public:

    int no;
    double koltukfiyat;
    string yolcuAdi;
    string cinsiyet;
    string durum;
    Koltuk *sonrakikoltuk;
    void ekle(int,double,string,string,string,Koltuk*);
    void listele(Koltuk*,int);
    void guncelle(int,double,string,string,string,Koltuk*);
    void BiletSat(Koltuk*);
};

class Sefer {

public :

    int seferno;
    string guzergah;
    string tarih;
    string saat;
    int kapasite;
    double biletfiyati;
    string plaka;
    string sofor;
    Koltuk *otobus;
    Sefer *sonrakisefer;
    Koltuk* ekle(int,string,string,int,double,string,string,string);
    void sil(int);
    void listele();
    int say();
    void gecmissefereaktar(int);
};

int SonSefer()
{
    ifstream sonseferno("sonsefer.txt",ios::out | ios::app);
    string oku;
    int sayi;
    if ( sonseferno.peek() == std::ifstream::traits_type::eof() )
    {
        sayi = 0;
    }
    else {
            getline(sonseferno, oku, '\n');
            sayi = stoi(oku);
    }
    sonseferno.close();
    return sayi;
}


Sefer *SeferHead;
int SonSeferNo = SonSefer();


void logayaz(string yazi)
{
    ofstream log("log.txt",ios::out | ios::app);
    string logagidenyazi;
    time_t simdikizaman = time(0);
    tm *yerelzaman = localtime(&simdikizaman);
    int gun,ay,yil,saat,dakika,saniye;
    yil = 1900 + yerelzaman->tm_year;
    ay = 1 + yerelzaman->tm_mon;
    gun = yerelzaman->tm_mday;
    saat = yerelzaman->tm_hour;
    dakika = yerelzaman->tm_min;
    saniye = yerelzaman->tm_sec;

    logagidenyazi = "("+to_string(gun)+"/"+to_string(ay)+"/"+to_string(yil)+" | "+to_string(saat)+":"+to_string(dakika)+":"+to_string(saniye)+") : "+yazi;
    log << logagidenyazi <<endl;
    log.close();
}

//Koltuk Islemleri

void Koltuk::BiletSat(Koltuk *SatilanKoltuk)
{
    string yolcuadif,adY,soyadY,cinsiyetf;
    char islem = 'Q';
    cout << "\nLutfen Satin Alan Yolcunun Ad Soyad Bilgisini Giriniz.. \n" <<endl;
    cin >> adY >> soyadY ;
    yolcuadif = adY+" "+soyadY;
    cout << "\nLutfen Satin Alan Yolcunun Cinsiyetini Giriniz..(Orn : Kadin/Erkek ) " <<endl<<endl;
    cin >> cinsiyetf;
    while(cinsiyetf!="Kadin" && cinsiyetf!="Erkek" && cinsiyetf!="kadin" && cinsiyetf!="erkek"){
        cout << "\nLutfen Satin Alan Yolcunun Cinsiyetini Ornege Bakarak Giriniz..(Orn : Kadin/Erkek ) " <<endl<<endl;
        cin >> cinsiyetf;
    }

    SatilanKoltuk->cinsiyet = cinsiyetf;
    SatilanKoltuk->yolcuAdi = yolcuadif;

    while(islem!='R'&&islem!='S') {
            cout << "\n  Rezervasyon Icin ---> 'R' || Satis Icin ---> 'S'  Tuslayiniz.. " <<endl<<endl;
            cin >> islem;
    }
    if(islem=='R')
        SatilanKoltuk->durum = "REZERVE";
    else
        SatilanKoltuk->durum = "SATILDI";
    }



void Koltuk::guncelle(int noF,double koltukfiyatiF,string durumF,string cinsiyetF,string yolcuAdiF,Koltuk* KoltukHead)
{
            while(KoltukHead->sonrakikoltuk!=0) {
                if(noF == KoltukHead->no)
                {
                    KoltukHead->cinsiyet = cinsiyetF;
                    KoltukHead->durum = durumF;
                    KoltukHead->yolcuAdi = yolcuAdiF;
                    KoltukHead->koltukfiyat = koltukfiyatiF;
                    break;
                }
            KoltukHead = KoltukHead->sonrakikoltuk;
            if(noF == KoltukHead->no)
                {
                    KoltukHead->cinsiyet = cinsiyetF;
                    KoltukHead->durum = durumF;
                    KoltukHead->yolcuAdi = yolcuAdiF;
                    KoltukHead->koltukfiyat = koltukfiyatiF;
                }
        }
}

void Koltuk::ekle(int noF,double koltukfiyatiF,string durumF,string cinsiyetF,string yolcuAdiF,Koltuk* KoltukHead)
{
        Koltuk *yenikoltuk = new Koltuk;
        yenikoltuk->no = noF;
        yenikoltuk->durum = durumF;
        yenikoltuk->koltukfiyat = koltukfiyatiF;
        yenikoltuk->cinsiyet = cinsiyetF;
        yenikoltuk->yolcuAdi = yolcuAdiF;
        yenikoltuk->sonrakikoltuk = 0;
        while(KoltukHead->sonrakikoltuk!=0) {
            KoltukHead = KoltukHead->sonrakikoltuk;
        }
        KoltukHead->sonrakikoltuk = yenikoltuk;
}

void BiletleriTxtyeYaz(int sefernoF, Koltuk* KoltukHead)
{
    string tarihF,saatF;
    Sefer *dolasici = SeferHead;
        if(dolasici==0){}
        else {
            while(dolasici) {
            if(dolasici->seferno == sefernoF) {
                    tarihF = dolasici->tarih;
                    saatF = dolasici->saat;
                }
                dolasici = dolasici->sonrakisefer;
            }
        }
    replace( tarihF.begin(), tarihF.end(), '/', '.');
    replace( saatF.begin(), saatF.end(), ':', '.');
    string dosyaadi = to_string(sefernoF)+" nolu Sefere Ait Koltuklar ("+tarihF+" I "+saatF+").txt";
    char cdosyaadi[dosyaadi.size()+1];
    strcpy(cdosyaadi, dosyaadi.c_str());
    remove( cdosyaadi );


    ofstream dosyabiletekle(dosyaadi,ios::out | ios::app);
    if(KoltukHead==0) {}
    else {
        while(KoltukHead) {
                dosyabiletekle << "Koltuk Numarasi :" << KoltukHead->no <<endl;
                dosyabiletekle << "Koltugun Durumu :" << KoltukHead->durum << endl;
                dosyabiletekle << "Yolcunun Ismi :" << KoltukHead->yolcuAdi << endl;
                dosyabiletekle << "Yolcunun Cinsiyeti :" << KoltukHead->cinsiyet << endl;
                dosyabiletekle << "Koltuk Fiyati :" << KoltukHead->koltukfiyat << endl;
                dosyabiletekle <<"---------------------------------------------------------------------------------" << endl;
                KoltukHead = KoltukHead->sonrakikoltuk;
        }
    }
    dosyabiletekle.close();
    logayaz(to_string(sefernoF)+" nolu sefere ait koltuklar guncellendi.");
}

void Koltuk::listele(Koltuk *KoltukHead,int sefernoF)
{
        if(KoltukHead==0)
        {
            cout<<"\n ISLEM YAPMAK ISTEDIGINIZ SEFER NUMARASINA AIT BIR KAYIT BULUNAMADI !.."<<endl<<endl;
        }
        else {
            cout<<"        **** "<<sefernoF<<" no'lu Sefer ****\n_________________________________________"<<endl<<endl;
            while(KoltukHead) {
                cout << "  Koltuk No : "<<KoltukHead->no<<"\n  Durumu    : "<<KoltukHead->durum<<"\n  Yolcu Adi : "<<KoltukHead->yolcuAdi<<"\n  Cinsiyeti : "<<KoltukHead->cinsiyet<<"\n  Bilet Fiyati : "<<KoltukHead->koltukfiyat<<"\n________________________________________________________________________________________________________" <<endl<<endl;
                KoltukHead = KoltukHead->sonrakikoltuk;
            }
        }
        logayaz(to_string(sefernoF)+" nolu sefere ait koltuklar listelendi.");
        BiletleriTxtyeYaz(sefernoF,KoltukHead);
}

int SatilmisBilet(Koltuk* KoltukHead) {
    int satilmisbiletler = 0;
        while(KoltukHead->sonrakikoltuk) {
            if(KoltukHead->durum != "BOS") {satilmisbiletler++;}
            KoltukHead = KoltukHead->sonrakikoltuk;
        }
        if(KoltukHead->durum!="BOS") {satilmisbiletler++;}
        return satilmisbiletler;
}

//Sefer Islemleri

void GecmisSeferListele()
{
    ifstream dosyagecmisseferlistele("GecmisSeferler.txt",ios::out | ios::app);
    string oku;
    if ( dosyagecmisseferlistele.peek() == std::ifstream::traits_type::eof() )
    {
        cout << "\n Gecmis Sefer Bulunamadi..." << endl;
    }
    else {
            cout<<"        |-|-| Gecmis Seferler |-|-|\n_________________________________________"<<endl<<endl;
        while (!dosyagecmisseferlistele.eof())
        {
            getline(dosyagecmisseferlistele, oku, '\n');
            cout << oku <<endl;
        }
    }
    dosyagecmisseferlistele.close();
    logayaz("Gecmis seferler listelendi.");
}

bool tarihkarsilastir(string tarih1,string saatl) {
    int sonuc = 0;
    time_t simdikizaman = time(0);
   tm *yerelzaman = localtime(&simdikizaman);
    int gun,ay,yil,saat,dakika;
   yil = 1900 + yerelzaman->tm_year;
   ay = 1 + yerelzaman->tm_mon;
   gun = yerelzaman->tm_mday;
   saat = yerelzaman->tm_hour;
   dakika = yerelzaman->tm_min;

   string fonkgun = tarih1.substr(0, tarih1.find("/"));
   tarih1.erase(0, fonkgun.length()+1);
   string fonkay = tarih1.substr(0, tarih1.find("/"));
   tarih1.erase(0, fonkay.length()+1);
   string fonkyil = tarih1;

   string fonksaat = saatl.substr(0, saatl.find(":"));
   saatl.erase(0, fonksaat.length()+1);
   string fonkdakika = saatl.substr(0, saatl.find("-"));
   saatl.erase(0, fonkdakika.length()+1);

   if(yil>stoi(fonkyil)) {
     sonuc = 1;
   }
   else if(yil==stoi(fonkyil)){
        if(ay>stoi(fonkay)) {
            sonuc = 1;
        }
        else if(ay==stoi(fonkay)){
            if(gun>stoi(fonkgun)) {
                sonuc = 1;
            }
            else if(gun==stoi(fonkgun)) {
                if(saat>stoi(fonksaat)) {
                    sonuc = 1;
                }
                else if(saat==stoi(fonksaat)) {
                    if(dakika>=stoi(fonkdakika)) {
                        sonuc=1;
                    }
                }
            }
        }
   }
   return sonuc;
}

void SeferleriTxtyeYaz()
{
    remove("EklenenSeferler.txt");
    ofstream dosyaseferekle("EklenenSeferler.txt",ios::out | ios::app);
    ofstream dosyagecmisseferekle("GecmisSeferler.txt",ios::out | ios::app);
    bool sonuc;

    Sefer *dolasici = SeferHead;
        if(dolasici==0){}

        else {
            while(dolasici) {
                    sonuc = tarihkarsilastir(dolasici->tarih,dolasici->saat);
                    if(!sonuc) {
                    dosyaseferekle << "Sefer Numarasi :"  << dolasici->seferno <<endl;
                    dosyaseferekle << "Sefer Tarihi :" << dolasici->tarih <<endl;
                    dosyaseferekle << "Sefer Saati :" << dolasici->saat <<endl;
                    dosyaseferekle << "Sefer Kapasitesi :" << dolasici->kapasite <<endl;
                    dosyaseferekle << "Sefer Bilet Fiyati :" << dolasici->biletfiyati <<endl;
                    dosyaseferekle << "Sefere Cikacak Otobus Plakasi :" << dolasici->plaka <<endl;
                    dosyaseferekle << "Sefer Cikacak Sofor Adi :" << dolasici->sofor << endl;
                    dosyaseferekle << "Sefer Guzergahi :" << dolasici->guzergah << endl;
                    dosyaseferekle <<"---------------------------------------------------------------------------------" << endl;
                    }
                    else {
                        dosyagecmisseferekle << "Sefer Numarasi :"  << dolasici->seferno <<endl;
                        dosyagecmisseferekle << "Sefer Tarihi :" << dolasici->tarih <<endl;
                        dosyagecmisseferekle << "Sefer Saati :" << dolasici->saat <<endl;
                        dosyagecmisseferekle << "Sefer Kapasitesi :" << dolasici->kapasite <<endl;
                        dosyagecmisseferekle << "Sefer Bilet Fiyati :" << dolasici->biletfiyati <<endl;
                        dosyagecmisseferekle << "Sefere Cikacak Otobus Plakasi :" << dolasici->plaka <<endl;
                        dosyagecmisseferekle << "Sefer Cikacak Sofor Adi :" << dolasici->sofor << endl;
                        dosyagecmisseferekle << "Sefer Guzergahi :" << dolasici->guzergah << endl;
                        dosyagecmisseferekle <<"---------------------------------------------------------------------------------" << endl;
                        Sefer t;
                        t.gecmissefereaktar(dolasici->seferno);
                        logayaz(to_string(dolasici->seferno)+" nolu seferin tarihi gectigi icin gecmis seferlere aktarildi.");
                    }
                    dolasici = dolasici->sonrakisefer;

            }
        }
        dosyaseferekle.close();
        logayaz("Seferler Guncellendi.");
}

void Sefer::sil(int seferF) {
    Sefer *dolasici = SeferHead;
    Sefer *gecici = dolasici;

    if(dolasici==0) {
        cout<<"\nSisteme Kayitli Sefer Bulunmamaktadir.."<<endl<<endl;
    }
    else if(dolasici->sonrakisefer==0 && dolasici->seferno == seferF) {
        if(SatilmisBilet(dolasici->otobus)==0) {
            SeferHead = 0;
            cout << "\n Silme Islemi Basariyla Gerceklesti.." <<endl<<endl;
            logayaz(to_string(seferF)+" nolu sefer silindi.");
        }
        else {
            cout << "\n DIKKAT ! SILMEK ISTEDIGINIZ SEFERDE BILET SATISI/REZERVASYONU GERCEKLESMIS OLDUGUNDAN SEFER SILME ISLEMI BASARISIZ OLDU .." <<endl<<endl;
            logayaz(to_string(seferF)+" nolu sefer silinmek istendi ancak bilet satisi/rezervasyonu gerceklesmis oldugundan sefer silme islemi basarisiz oldu.");
        }
    }
    else if(dolasici==SeferHead && dolasici->seferno == seferF)
    {
        if(SatilmisBilet(dolasici->otobus)==0) {
            SeferHead = dolasici->sonrakisefer;
            cout << "\n Silme Islemi Basariyla Gerceklesti.." <<endl<<endl;
            logayaz(to_string(seferF)+" nolu sefer silindi.");
        }
        else {
            cout << "\n DIKKAT ! SILMEK ISTEDIGINIZ SEFERDE BILET SATISI/REZERVASYONU GERCEKLESMIS OLDUGUNDAN SEFER SILME ISLEMI BASARISIZ OLDU .." <<endl<<endl;
            logayaz(to_string(seferF)+" nolu sefer silinmek istendi ancak bilet satisi/rezervasyonu gerceklesmis oldugundan sefer silme islemi basarisiz oldu.");
        }
    }
    else {
        dolasici = dolasici->sonrakisefer;
        while(dolasici) {
            if(dolasici->seferno == seferF) {
                if(SatilmisBilet(dolasici->otobus)==0)
                {
                    gecici->sonrakisefer = dolasici->sonrakisefer;
                    cout << "\n Silme Islemi Basariyla Gerceklesti.." <<endl<<endl;
                    logayaz(to_string(seferF)+" nolu sefer silindi.");
                    break;
                }
                else {
                    logayaz(to_string(seferF)+" nolu sefer silinmek istendi ancak bilet satisi/rezervasyonu gerceklesmis oldugundan sefer silme islemi basarisiz oldu.");
                    cout << "\n DIKKAT ! SILMEK ISTEDIGINIZ SEFERDE BILET SATISI/REZERVASYONU GERCEKLESMIS OLDUGUNDAN SEFER SILME ISLEMI BASARISIZ OLDU .." <<endl<<endl;
                }
            }
            dolasici = dolasici->sonrakisefer;
            gecici = gecici->sonrakisefer;
        }
    }
}

void Sefer::gecmissefereaktar(int seferF) {
    Sefer *dolasici = SeferHead;
    Sefer *gecici = dolasici;

    if(dolasici==0) {

    }
    else if(dolasici->sonrakisefer==0 && dolasici->seferno == seferF) {

            SeferHead = 0;
    }
    else if(dolasici==SeferHead && dolasici->seferno == seferF)
    {
            SeferHead = dolasici->sonrakisefer;
    }
    else {
        dolasici = dolasici->sonrakisefer;
        while(dolasici) {
            if(dolasici->seferno == seferF) {
                    gecici->sonrakisefer = dolasici->sonrakisefer;
                    break;
            }
            dolasici = dolasici->sonrakisefer;
            gecici = gecici->sonrakisefer;
        }
    }
}

Koltuk* Sefer::ekle(int seferF,string tarihF,string saatF,int kapasiteF,double biletfiyatiF,string plakaF,string soforF,string guzergahF)
    {
        Sefer *yenisefer = new Sefer;
        yenisefer->seferno = seferF;
        yenisefer->tarih = tarihF;
        yenisefer->saat = saatF;
        yenisefer->kapasite = kapasiteF;
        yenisefer->biletfiyati = biletfiyatiF;
        yenisefer->plaka = plakaF;
        yenisefer->sofor = soforF;
        yenisefer->guzergah = guzergahF;
        yenisefer->sonrakisefer = 0;

        Sefer *dolasici = SeferHead;
        if(dolasici==0) {
            SeferHead = yenisefer;
        }
        else {
            while(dolasici->sonrakisefer!=0) {
                dolasici = dolasici->sonrakisefer;
            }
            dolasici->sonrakisefer = yenisefer;
        }
            Koltuk *yenikoltuk = new Koltuk;
            yenikoltuk->no = 1;
            yenikoltuk->cinsiyet = "-";
            yenikoltuk->durum = "BOS";
            yenikoltuk->koltukfiyat = biletfiyatiF;
            yenikoltuk->sonrakikoltuk = 0;
            yenikoltuk->yolcuAdi = "-";
            yenisefer->otobus = yenikoltuk;
        for(int y = 1;y<kapasiteF;y++) {
                Koltuk a;
                a.ekle(y+1,biletfiyatiF,"BOS","-","-",yenisefer->otobus);

        }
        return yenisefer->otobus;
    }

    int Sefer::say()
    {
        int i =0;
        Sefer *dolasici = SeferHead;
        while(dolasici) {
            dolasici = dolasici->sonrakisefer;
            i++;
        }
        return i;
    }

    void Sefer::listele()
    {
        Sefer *dolasici = SeferHead;
        if(dolasici==0)
        {
            cout<<"\nSisteme Kayitli Sefer Bulunmamaktadir.."<<endl<<endl;
        }
        else {
            cout<<"        **** Seferler ****\n_________________________________________"<<endl<<endl;
            while(dolasici) {
                cout << "  Sefer No : "<<dolasici->seferno<<"\n  Guzergah : "<<dolasici->guzergah<<"\n  Tarih : "<<dolasici->tarih<<"\n  Saat : "<<dolasici->saat<<"\n  Kapasite : "<<dolasici->kapasite<<"\n  Bilet Fiyati : "<<dolasici->biletfiyati<<"\n  Arac Plakasi : "<<dolasici->plaka<<"\n  Arac Soforu : "<<dolasici->sofor<<"\n________________________________________________________________________________________________________" <<endl<<endl;
                dolasici = dolasici->sonrakisefer;
            }
        }
        SeferleriTxtyeYaz();
        logayaz("Seferler listelendi.");
}

string parsela(string s,string ayirmabolgesi)
{
    string donecektarih;
    string silinecekbolum = s.substr(0, s.find(ayirmabolgesi));
    s.erase(0, silinecekbolum.length()+ayirmabolgesi.length());
    return s;
}

int main()
{
    ifstream dosyaseferlistele("EklenenSeferler.txt",ios::out | ios::app);
    int sefernumx,koltuknumTx;
    int seferkapasitex;
    double seferbiletfiyatix,fiyatTx;
    string sefernum,koltuknumT;
    string sefertarih,yolcuAdiT;
    string sefersaati,durumT;
    string seferkapasite,cinsiyetT;
    string seferbiletfiyati,fiyatT;
    string seferplaka;
    string sefersofor;
    string seferguzergah;
    string silinecekbolum;

    regex regDate("\\d{2}/\\d{2}/\\d{4}");
    smatch match;
    regex regTime("([0-1][0-9]|[2][0-3]):([0-5][0-9])-([0-1][0-9]|[2][0-3]):([0-5][0-9])");

    //dosya bos mu kontrolu
    if ( dosyaseferlistele.peek() == std::ifstream::traits_type::eof() )
    {}
    else {
        while (!dosyaseferlistele.eof())
        {
            getline(dosyaseferlistele, sefernum, '\n');
            if(sefernum!="") {
            sefernum = parsela(sefernum,":");
            sefernumx = stoi(sefernum);
            getline(dosyaseferlistele, sefertarih, '\n');
            sefertarih = parsela(sefertarih,":");
            getline(dosyaseferlistele, sefersaati, '\n');
            sefersaati = parsela(sefersaati,":");
            getline(dosyaseferlistele, seferkapasite, '\n');
            seferkapasite = parsela(seferkapasite,":");
            seferkapasitex = stoi(seferkapasite);
            getline(dosyaseferlistele, seferbiletfiyati, '\n');
            seferbiletfiyati = parsela(seferbiletfiyati,":");
            seferbiletfiyatix = stod(seferbiletfiyati);
            getline(dosyaseferlistele, seferplaka, '\n');
            seferplaka = parsela(seferplaka,":");
            getline(dosyaseferlistele, sefersofor, '\n');
            sefersofor = parsela(sefersofor,":");
            getline(dosyaseferlistele, seferguzergah, '\n');
            seferguzergah = parsela(seferguzergah,":");
            getline(dosyaseferlistele,silinecekbolum, '\n');
            Sefer a;
            Koltuk *KoltukHead = a.ekle(sefernumx,sefertarih,sefersaati,seferkapasitex,seferbiletfiyatix,seferplaka,sefersofor,seferguzergah);
            string tarihK = sefertarih;
            string saatK = sefersaati;
            replace( tarihK.begin(), tarihK.end(), '/', '.');
            replace( saatK.begin(), saatK.end(), ':', '.');
            ifstream dosyabiletlistele(sefernum+" nolu Sefere Ait Koltuklar ("+tarihK+" I "+saatK+").txt",ios::out | ios::app);
             while (!dosyabiletlistele.eof())
        {
            getline(dosyabiletlistele, koltuknumT, '\n');
            if(koltuknumT!="") {
            koltuknumT = parsela(koltuknumT,":");
            koltuknumTx = stoi(koltuknumT);

            getline(dosyabiletlistele, durumT, '\n');
            durumT = parsela(durumT,":");

            getline(dosyabiletlistele, yolcuAdiT, '\n');
            yolcuAdiT = parsela(yolcuAdiT,":");

            getline(dosyabiletlistele, cinsiyetT, '\n');
            cinsiyetT = parsela(cinsiyetT,":");

            getline(dosyabiletlistele, fiyatT, '\n');
            fiyatT = parsela(fiyatT,":");
            fiyatTx = stod(fiyatT);

            getline(dosyabiletlistele,silinecekbolum, '\n');
            Koltuk c;
            c.guncelle(koltuknumTx,fiyatTx,durumT,cinsiyetT,yolcuAdiT,KoltukHead);
            }
        }
            dosyabiletlistele.close();
            }
        }
    }
    dosyaseferlistele.close();
    int giris=1;
    int sefergiris = 1;
    int biletgiris = 1;
    int biletgiris2 = 1;
    char seferislem;
    char biletislem;
    char islem;
    char biletislem2;
    while(giris!=0) {
        sefergiris = 1;
        biletgiris = 1;
        cout<<"-----------------"<< endl;
        cout<<"|               |"<<endl;
        cout<<"|      G&M      |" <<endl;
        cout<<"|    SEYAHAT    |"<<endl;
        cout<<"|               |"<<endl;
        cout<<"-----------------"<< endl;
        cout<<"---------------------------------------\nSefer Islemleri Icin ----> 'S' \nBilet Satis Islemleri Icin ----> 'B'\nCikis Icin ----> 'C'\n---------------------------------------"<<endl<<endl;
        cin>>islem;
        cout<<"\n\n"<<endl;

  //Sefer Y?lemleri
        if(islem=='S' || islem =='s')
            {
                while(sefergiris!=0) {
                cout<<"        ^^^^ Sefer Islemleri ^^^^\n_________________________________________"<<endl<<endl;
                cout<<"  Sefer Listelemek Icin ----> 'L' \n  Sefer Eklemek Icin ----> 'E' \n  Sefer Silmek Icin ----> 'S' \n  Sefer Gelir Hesaplari Icin ----> 'G' \n  Toplam Sefer Sayisi Icin ----> 'T' \n  Gecmis Seferleri Listelemek Icin ----> 'O' \n  Sofor Degisimi Icin ----> 'D' \n  Onceki Menuye Donmek Icin ----> 'B' \n  Programi Sonlandirmak Icin ----> 'C' \n\ntusuna basiniz.. \n_________________________________________"<<endl<<endl;
                cin>>seferislem;
                cout<<"\n"<<endl;

                    if(seferislem=='L' || seferislem=='l')
                        {
                            Sefer a;
                            a.listele();
                        }
                    else if(seferislem=='E' || seferislem=='e')
                        {

                            int kapasiteE,guzergahSecim;
                            string guzergahE,tarihE,saatE,plakaE,soforE;
                            double biletfiyatiE;
                            char onay = 'Y';

                            while(onay!='E')
                            {
                            cout << "\nLutfen sefer guzergahini seciniz : \n" <<endl;
                            cout << "  1 - Kocaeli >> Ankara \n  2 - Ankara >> Kocaeli \n  3 - Kocaeli >> Istanbul \n  4 - Istanbul >> Kocaeli \n  5 - Kocaeli >> Izmir \n  6 - Izmir >> Kocaeli"<<endl<<endl;
                            cin>>guzergahSecim;
                            if(guzergahSecim == 1)
                            {
                                guzergahE = "Kocaeli >> Ankara";
                            }
                            else if(guzergahSecim == 2)
                            {
                                guzergahE = "Ankara >> Kocaeli";
                            }
                            else if(guzergahSecim == 3)
                            {
                                guzergahE = "Kocaeli >> Istanbul";
                            }
                            else if(guzergahSecim == 4)
                            {
                                guzergahE = "Istanbul >> Kocaeli";
                            }
                            else if(guzergahSecim == 5)
                            {
                                guzergahE = "Kocaeli >> Izmir";
                            }
                            else if(guzergahSecim == 6)
                            {
                                guzergahE = "Izmir >> Kocaeli";
                            }
                            else
                            {
                                while(guzergahSecim!=1&&guzergahSecim!=2&&guzergahSecim!=3&&guzergahSecim!=4&&guzergahSecim!=5&&guzergahSecim!=6)
                                {
                                    cout << "Lutfen Var Olan Seceneklerden Birini Seciniz.." << endl;
                                    cin >> guzergahSecim;
                                }
                            }
                            cout << "\nLutfen seferin arac kapasitesini giriniz : \n" << endl;
                            cin >> kapasiteE;
                            cout << "\nLutfen seferin tarihini giriniz(Orn : 05/02/2020) : \n" <<endl;
                            cin >> tarihE;
                            while(!regex_match(tarihE, match, regDate)){
                                cout << "\nLutfen sefer tarihini ornekte verildigi gibi giriniz(Orn : 05/02/2020) : \n" <<endl;
                                cin >> tarihE;
                            }


                            cout << "\nLutfen sefer saatini giriniz(Orn : 16:05 - 18:05) : \n" <<endl;
                            cin >> saatE;
                             while(!regex_match(saatE, regTime)){
                                cout << "\nLutfen sefer saatini ornekte verildigi gibi giriniz(Orn :  16:05 - 18:05) : \n" <<endl;
                                cin >> saatE;
                            }
                            bool gecmismi = tarihkarsilastir(tarihE,saatE);
                            while(gecmismi) {
                                cout << "\nGirmis oldugunuz tarih ve saat gecmis bir zamana aittir. Gecmis tarihe sefer girilememektedir. Lutfen uygun bir zaman giriniz.. \n" <<endl;

                                cout << "\nLutfen seferin tarihini giriniz(Orn : 05/02/2020) : \n" <<endl;
                                cin >> tarihE;
                                while(!regex_match(tarihE, match, regDate)){
                                    cout << "\nLutfen sefer tarihini ornekte verildigi gibi giriniz(Orn : 05/02/2020) : \n" <<endl;
                                    cin >> tarihE;
                                }
                                cout << "\nLutfen sefer saatini giriniz(Orn : 16:05-18:05) : \n" <<endl;
                                cin >> saatE;
                                while(!regex_match(saatE, regTime)){
                                    cout << "\nLutfen sefer saatini ornekte verildigi gibi giriniz(Orn :  16:05 - 18:05) : \n" <<endl;
                                    cin >> saatE;
                                }
                                gecmismi = tarihkarsilastir(tarihE,saatE);
                            }

                            cout << "\nLutfen sefere cikacak aracin plakasini giriniz : \n" <<endl;
                            cin >> plakaE;
                            string soyadE;
                            string adE;
                            cout << "\nLutfen sefere cikacak soforun Ad Soyad bilgisini giriniz : \n" <<endl;
                            cin >> adE >> soyadE;
                            soforE = adE+" "+soyadE;
                            cout << "\nLutfen tane bilet fiyatini giriniz(Orn : 15.50) : \n"<<endl;
                            cin >> biletfiyatiE;

                            //Bilgileri gösterip Onay istiyor
                            cout << "_______________________\nSeferin Son Hali : \n\n  Guzergah : "<<guzergahE<<"\n  Kapasite : "<<kapasiteE<<"\n  Tarih : "<<tarihE<<"\n  Saat : "<<saatE<<"\n  Arac Plakasi : "<<plakaE<<"\n  Arac Soforu : "<<soforE<<"\n  Bilet Fiyati(Adet) : "<<biletfiyatiE<<endl<<endl;
                            cout << "Seferi Onaylamak Icin ----> 'E' \nIptal Etmek Icin ----> 'H' \nBilgileri Bastan Duzenlemek Icin ise Herhangi Bir Tusa Basiniz... "<<endl<<endl;
                            cin>>onay;
                            if(onay == 'H') {break;}
                            else if(onay == 'E') {
                               Sefer a;
                               int i = a.say();
                               i++;
                               Koltuk *e = a.ekle(SonSeferNo+1,tarihE,saatE,kapasiteE,biletfiyatiE,plakaE,soforE,guzergahE);
                               logayaz(to_string(i)+" nolu sefer sisteme eklendi.");
                               SonSeferNo++;
                               remove("sonsefer.txt");
                               ofstream sonsfrdegistir("sonsefer.txt",ios::out | ios::app);
                               sonsfrdegistir << SonSeferNo <<endl;
                               sonsfrdegistir.close();
                            }

                            }


                    }
                    else if(seferislem=='S' || seferislem=='s')
                        {
                            int sefernoE;
                            cout << "\nLutfen silmek istediginiz seferin, sefer numarasini giriniz : \n" << endl;
                            cin >> sefernoE;
                            Sefer a;


                            //Koltuk txtsini silme
                            Sefer *dolasici = SeferHead;
                            string tarihK,saatK;
                            while(dolasici) {
                                if(dolasici->seferno == sefernoE) {
                                    tarihK = dolasici->tarih;
                                    saatK = dolasici->saat;
                                }
                                dolasici = dolasici->sonrakisefer;
                            }
                            replace( tarihK.begin(), tarihK.end(), '/', '.');
                            replace( saatK.begin(), saatK.end(), ':', '.');
                            string dosyaadi = to_string(sefernoE)+" nolu Sefere Ait Koltuklar ("+tarihK+" I "+saatK+").txt";
                            char cdosyaadi[dosyaadi.size()+1];
                            strcpy(cdosyaadi, dosyaadi.c_str());
                            remove(cdosyaadi);
                            a.sil(sefernoE);
                        }




                    else if(seferislem=='G' || seferislem=='g')
                        {
                            int sefernoE,kapasite;
                            Koltuk *KoltukHead = 0;
                            double toplamkar,satilmisbiletkari,biletfiyati;
                            cout << "\nLutfen gelir hesabi yapmak istediginiz seferin, sefer numarasini giriniz : \n" << endl;
                            cin >> sefernoE;
                            Sefer *dolasici = SeferHead;
                            while(dolasici) {
                                if(dolasici->seferno == sefernoE) {
                                    KoltukHead = dolasici->otobus;
                                    biletfiyati = dolasici->biletfiyati;
                                    kapasite = dolasici->kapasite;
                                    break;
                                }
                                dolasici = dolasici->sonrakisefer;
                            }
                            if(KoltukHead) {
                                satilmisbiletkari = SatilmisBilet(KoltukHead);
                                satilmisbiletkari = satilmisbiletkari*biletfiyati;
                                toplamkar = kapasite*biletfiyati;

                                cout <<"\n Satilan Bilet Sayisina Gore Hesaplanan Gelir : " <<satilmisbiletkari<<"TL "<<endl;
                                cout <<"\n Tum Biletlerin Satilmasi Halinde Hesaplanan Gelir : " <<toplamkar<<"TL "<<endl<<endl;
                                logayaz(to_string(sefernoE)+" nolu seferin hesaplanan geliri : "+to_string(satilmisbiletkari)+"TL olarak listelendi.");
                            }
                            else {
                                cout<<"\n GIRDIGINIZ SEFER NUMARASINA AIT BIR KAYIT BULUNAMADI !.."<<endl<<endl;
                            }

                        }
                    else if(seferislem=='T' || seferislem=='t')
                        {
                            Sefer a;
                            int i = a.say();
                            cout << "\n  Aktif Sefer Sayisi : "<<i<<endl;
                            cout << "\n  Toplam Sefer Sayisi : "<<SonSeferNo<<endl<<endl;
                            logayaz("Aktif Sefer Sayisi : "+to_string(i)+" olarak listelendi.");
                            logayaz("Toplam Sefer Sayisi : "+to_string(SonSeferNo)+" olarak listelendi.");
                        }
                    else if(seferislem=='O' || seferislem=='o')
                        {
                            GecmisSeferListele();
                        }
                    else if(seferislem=='D' || seferislem=='d')
                        {
                            int sefernoE;
                            bool kontrol = false;
                            string SoforadiE;
                            cout << "\nLutfen sofor degistirmek istediginiz seferin, sefer numarasini giriniz : \n" << endl;
                            cin >> sefernoE;
                            string yad, ysoyad,eskisofor;
                            cout << "\nLutfen yeni soforun Ad Soyad bilgilerini giriniz : \n" << endl;
                            cin >> yad >>ysoyad;
                            SoforadiE = yad + " " + ysoyad;
                            Sefer *dolasici = SeferHead;
                            while(dolasici) {
                                if(dolasici->seferno == sefernoE) {
                                    eskisofor = dolasici->sofor;
                                    dolasici->sofor = SoforadiE;
                                    kontrol = true;
                                }
                                dolasici = dolasici->sonrakisefer;
                            }
                            if(kontrol) {
                                cout<<"\n Isleminiz Basariyla Gerceklesti.."<<endl<<endl;
                                logayaz(to_string(sefernoE)+" nolu seferin Soforu '"+eskisofor+"' iken --> '"+SoforadiE+"' olarak guncellendi.");
                            }
                            else {
                                cout<<"\n GIRDIGINIZ SEFER NUMARASINA AIT BIR KAYIT BULUNAMADI !.."<<endl<<endl;
                            }

                        }
                    else if(seferislem=='B' || seferislem=='b')
                        {
                            //Onceki Menu
                            sefergiris=0;
                            giris=1;
                        }
                    else if(seferislem=='C' || seferislem=='c')
                        {
                            //Programi Sonlandir
                            giris=0;
                            biletgiris=0;
                            sefergiris=0;
                            biletgiris2 = 0;
                            Sefer *dolasiciR = SeferHead;
                        if(dolasiciR==0)
                            {}
                        else {
                                while(dolasiciR) {
                                    BiletleriTxtyeYaz(dolasiciR->seferno,dolasiciR->otobus);
                                    dolasiciR = dolasiciR->sonrakisefer;
                                }
                            }

                        SeferleriTxtyeYaz();
                        }
                    else
                        {
                            cout<<"______________________________________________________________________________________\nLutfen Asagidaki Islemlerden Birini Giriniz.."<<endl<<endl;
                        }

              }
          }

 //Bilet Y?lemleri
        else if(islem=='B' || islem=='b')
            {
                int sefernoE,koltuknoE,biletsatiskontrol;
                Koltuk *KoltukHead;
                while(biletgiris!=0)
                {
                    KoltukHead = 0;
                    cout<<"        ^^^^ Bilet Islemleri ^^^^\n_________________________________________"<<endl<<endl;
                    cout<<"  Mevcut Seferleri Listelemek Icin ----> 'L' \n  Onceki Menuye Donmek Icin ----> 'B' \n  Programi Sonlandirmak Icin ----> 'C' \n\ntusuna basiniz.. \n_________________________________________"<<endl<<endl;
                    cin>>biletislem;
                    cout<<"\n"<<endl;
                    if(biletislem=='L'||biletislem=='l')
                    {
                        Sefer a;
                        a.listele();
                        cout << "\nLutfen Islem Yapmak Istediginiz Seferin, Sefer Numarasini Giriniz : \n" << endl;
                        cin >> sefernoE;
                        Sefer *dolasici = SeferHead;
                            while(dolasici) {
                                if(dolasici->seferno == sefernoE) {
                                    KoltukHead = dolasici->otobus;
                                }
                                dolasici = dolasici->sonrakisefer;
                            }
                        Koltuk b;
                        b.listele(KoltukHead,sefernoE);
                        biletgiris2 = 1;

                        while(biletgiris2!=0) {
                        biletsatiskontrol = 0;
                        cout<<"\n\n  Bilet Satis Islemleri Icin ----> 'S' \n  Satis Iptal Islemleri Icin ----> 'I' \n  Onceki Menuye Donmek Icin ----> 'B' \n  Programi Sonlandirmak Icin ----> 'C' \n\ntusuna basiniz.. \n_________________________________________"<<endl<<endl;
                        cin >> biletislem2;
                        cout<<"\n"<<endl;
                        if(biletislem2=='S'||biletislem2=='s')
                        {
                            cout << "\nLutfen Satis Islemi Yapilacak Koltugun, Koltuk Numarasini Giriniz : \n" << endl;
                            cin >> koltuknoE;
                            Koltuk *koltukdolas = KoltukHead;
                            while(koltukdolas) {
                                if(koltukdolas->no == koltuknoE) {
                                    if(koltukdolas->durum=="BOS") {
                                        biletsatiskontrol = 1;
                                        b.BiletSat(koltukdolas);
                                        logayaz(to_string(sefernoE)+" nolu seferin "+to_string(koltuknoE)+". koltuðununun satis islemi gerceklestirildi.");
                                    }
                                    else if(koltukdolas->durum=="REZERVE")
                                    {
                                        biletsatiskontrol = 1;
                                        char rezervdevam;
                                        cout<<"\n GIRDIGINIZ KOLTUK REZERVE GORUNMEKTEDIR, YINE DE SATISA DEVAM ETMEK ISTIYOR MUSUNUZ ? (E/H)"<<endl<<endl;
                                        cin >> rezervdevam;
                                        if(rezervdevam == 'E'||rezervdevam == 'e') {
                                            b.BiletSat(koltukdolas);
                                            logayaz(to_string(sefernoE)+" nolu seferin "+to_string(koltuknoE)+". koltuðununun satis islemi gerceklestirildi.");
                                        }
                                    }
                                    else
                                    {
                                        biletsatiskontrol = 2;
                                        cout<<"\n GIRDIGINIZ KOLTUK ZATEN SATILMIS, LUTFEN BOS KOLTUKLARDAN BIRINI SECINIZ !.."<<endl<<endl;
                                    }
                                }
                                koltukdolas = koltukdolas->sonrakikoltuk;
                            }
                            if(biletsatiskontrol == 1) {
                                cout<<"\n Isleminiz Basariyla Gerceklesti.."<<endl<<endl;
                                b.listele(KoltukHead,sefernoE);
                            }
                            else if(biletsatiskontrol == 0) {
                                cout<<"\n GIRDIGINIZ SEFER NUMARASINA AIT BIR KAYIT BULUNAMADI !.."<<endl<<endl;
                            }
                            BiletleriTxtyeYaz(sefernoE,KoltukHead);
                        }
                        else if(biletislem2=='I'||biletislem2=='i')
                        {
                             char onay;
                             cout << "\nLutfen Iptal Islemi Yapilacak Koltugun, Koltuk Numarasini Giriniz : \n" << endl;
                             cin >> koltuknoE;
                             Koltuk *koltukdolas = KoltukHead;

                             while(koltukdolas) {
                                if(koltukdolas->no == koltuknoE)
                                {
                                    if(koltukdolas->durum=="BOS")
                                        cout << "\n SECMIS OLDUGUNUZ KOLTUK ZATEN SATILMAMIS !.. \n" << endl;
                                    else
                                    {
                                        cout << "\n\n  Koltuk No : "<<koltukdolas->no<<"\n  Durumu    : "<<koltukdolas->durum<<"\n  Yolcu Adi : "<<koltukdolas->yolcuAdi<<"\n  Cinsiyeti : "<<koltukdolas->cinsiyet<<"\n  Bilet Fiyati : "<<koltukdolas->koltukfiyat<<endl<<endl;
                                        cout << "\nIptal Etmek Istediginizden Emin misiniz ? (E/H)" <<endl<<endl;
                                        cin >> onay;
                                        if(onay == 'E' || onay == 'e')
                                        {
                                            koltukdolas->cinsiyet = "-";
                                            koltukdolas->yolcuAdi = "-";
                                            koltukdolas->durum = "BOS";
                                            logayaz(to_string(sefernoE)+" nolu seferin "+to_string(koltuknoE)+". koltuðunun satisi iptal edildi.");
                                            cout << "\nIslem Basarili.." <<endl;
                                        }
                                        else
                                        {
                                            cout << "\nIslem Iptal Edildi.." <<endl<<endl;
                                        }
                                    }
                                }
                                koltukdolas = koltukdolas->sonrakikoltuk;
                             }

                        }
                        else if(biletislem2=='B'||biletislem2=='b')
                        {
                            //Onceki Menu
                            biletgiris=1;
                            biletgiris2 = 0;
                            giris=1;
                        }
                        else if(biletislem2=='C'||biletislem2=='c')
                        {
                            //Programi Sonlandir
                            giris=0;
                            biletgiris=0;
                            sefergiris=0;
                            biletgiris2 = 0;
                            Sefer *dolasiciD = SeferHead;
                        if(dolasiciD==0)
                            {}
                        else {
                                while(dolasiciD) {
                                    BiletleriTxtyeYaz(dolasiciD->seferno,dolasiciD->otobus);
                                    dolasiciD = dolasiciD->sonrakisefer;
                                }
                            }

                        SeferleriTxtyeYaz();
                        }
                    }
                }

                else if(biletislem=='B' || biletislem=='b')
                    {
                        //Onceki Menu
                        biletgiris=0;
                        biletgiris2 = 0;
                        giris=1;
                    }
                else if(biletislem=='C' || biletislem=='c')
                    {
                        //Programi Sonlandir
                        giris=0;
                        biletgiris=0;
                        sefergiris=0;
                        biletgiris2 = 0;
                        Sefer *dolasiciC = SeferHead;
                        if(dolasiciC==0)
                            {}
                        else {
                                while(dolasiciC) {
                                    BiletleriTxtyeYaz(dolasiciC->seferno,dolasiciC->otobus);
                                    dolasiciC = dolasiciC->sonrakisefer;
                                }
                            }

                        SeferleriTxtyeYaz();
                    }
                else
                    {
                        cout<<"______________________________________________________________________________________\nLutfen Asagidaki Islemlerden Birini Giriniz.."<<endl<<endl;
                    }
            }
        }
        else if(islem=='C' || islem=='c')
        {
            //Programi Sonlandir
                            giris=0;
                            biletgiris=0;
                            sefergiris=0;
                            biletgiris2 = 0;
                            Sefer *dolasiciQ = SeferHead;
                        if(dolasiciQ==0)
                            {}
                        else {
                                while(dolasiciQ) {
                                    BiletleriTxtyeYaz(dolasiciQ->seferno,dolasiciQ->otobus);
                                    dolasiciQ = dolasiciQ->sonrakisefer;
                                }
                            }

                        SeferleriTxtyeYaz();
        }

        else
            {
                cout<<"______________________________________________________________________________________\nLutfen Asagidaki Islemlerden Birini Giriniz.."<<endl<<endl;
            }
    }

}
