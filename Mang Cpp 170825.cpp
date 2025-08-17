#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <array>
using namespace std;

template <class kieu_du_lieu, int sl>
class mang
{
public:
    int so_luong;
    kieu_du_lieu* dia_chi;
    mang()
    {
        so_luong = sl;
        dia_chi = (kieu_du_lieu*)calloc(so_luong, sizeof(kieu_du_lieu));
    }

    kieu_du_lieu& operator[](int i)
    {
        if ((i < 0) || (i >= so_luong))
            throw runtime_error("vuot qua kich thuoc cua mang");
        return dia_chi[i];
    }

    ~mang()
    {
        free(dia_chi);
    }
};

class mang_co_dan
{
public:
    int so_luong;
    int* dia_chi;

    mang_co_dan(int kich_thuoc_ban_dau = 0)
    {
        so_luong = kich_thuoc_ban_dau;
        if (so_luong > 0)
            dia_chi = (int*)calloc(so_luong, sizeof(int));
        else
            dia_chi = NULL;
    }

    // Overload toán tử []
    int& operator[](int i)
    {
        if ((i < 0) || (i >= so_luong))
            throw runtime_error("vuot qua kich thuoc cua mang");
        return dia_chi[i];
    }

    const int& operator[](int i) const
    {
        if ((i < 0) || (i >= so_luong))
            throw runtime_error("vuot qua kich thuoc cua mang");
        return dia_chi[i];
    }

    void thay_doi_kich_thuoc(int kich_thuoc_moi) {
        if (kich_thuoc_moi <= 0)
        {
            free(dia_chi);
            dia_chi = NULL;
            so_luong = 0;
            return;
        }
        int* dia_chi_moi = (int*)calloc(kich_thuoc_moi, sizeof(int));

        int min_size;
        if (so_luong < kich_thuoc_moi)
            min_size = so_luong;
        else
            min_size = kich_thuoc_moi;

        for (int i = 0; i < min_size; i++)
        {
            dia_chi_moi[i] = dia_chi[i];
        }
        free(dia_chi);
        dia_chi = dia_chi_moi;
        so_luong = kich_thuoc_moi;
    }

    ~mang_co_dan()
    {
        free(dia_chi);
    }
};

int main() {
    mang <int, 3> a;
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    for (int i = 0; i < a.so_luong; i++) {
        cout << "a[" << i << "] = " << a[i] << endl;
    }

    mang_co_dan b(2);
    b[0] = 5;
    b[1] = 15;

    cout << "Mang co dan ban dau: " << endl;
    for (int i = 0; i < b.so_luong; i++) {
        cout << "b[" << i << "] = " << b[i] << endl;
    }

    b.thay_doi_kich_thuoc(4);
    b[2] = 25;
    b[3] = 35;

    cout << "Sau khi thay doi kich thuoc: " << endl;
    for (int i = 0; i < b.so_luong; i++) {
        cout << "b[" << i << "] = " << b[i] << endl;
    }

    return 0;
}
