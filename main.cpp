#include <windows.h>
#include "function.h"

int main()
{
    system("cls");
    PTR_ChuyenBay First_CB = NULL;
    List_MayBay list_MB;
    PTR_HK root_HK = NULL;

    Init_Main(list_MB, First_CB, root_HK);

    check_HoanTat_All(First_CB, list_MB);

    int key_1;
    int exit = 0;
    while (1)
    {
        Clear_Frame_Main();
        key_1 = SelectLV1();
        exit = 0;
        switch (key_1)
        {
        case -1:
        {
            After_Main(list_MB, First_CB, root_HK);
            return 0;
        }
        case 0:
        {
            QuanLyMayBay(list_MB);
            break;
        case 1:
        {
            int key_2_2;
            while (exit == 0)
            {
                key_2_2 = SelectLV2_2();
                switch (key_2_2)
                {
                case -1:
                {
                    exit = 1;
                    break;
                }
                case 0:
                {
                    XuLyDSChuyenBay(First_CB, root_HK, list_MB);
                    break;
                }
                case 1:
                {
                    DatVe(First_CB, root_HK);
                    break;
                }
                case 2:
                {
                    HuyVe(First_CB, root_HK);
                    break;
                }
                case 3:
                {
                    DanhSachGheTrong(First_CB, list_MB);
                    break;
                }
                case 4:
                {
                    ThongKeChuyenBay(list_MB);
                    break;
                }
                }
            }
        }
        }
        }
    }
}
