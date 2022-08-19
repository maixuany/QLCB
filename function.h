#pragma once
#include <conio.h>
#include <cstring>
#include "console.h"
#include <string>
#include "entity.h"
#include "file.h"

using namespace std;

//Menu
int SelectLV1();
int SelectLV2_1();
int SelectLV2_2();

//Y
int Insert_MB(List_MayBay &list, MayBay *maybay);
void show_List_MB(List_MayBay list, int page_now);
void Deletedequi(PTR_HK &root_HK);
int dem_CB(PTR_ChuyenBay list, string status);
PTR_ChuyenBay hanhkhach_chuahoanthanhchuyenbay(PTR_ChuyenBay list_CB, char *CMND);
PTR_ChuyenBay check_maCB_chuabay(PTR_ChuyenBay list_CB, char *maCB);
void show_List_CB(PTR_ChuyenBay l, int page_now, int count_CB, string status);
int DatVe(PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void Init_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void Handle_Main();
void deleteListCB(PTR_ChuyenBay &First);
void deleteListMB(List_MayBay &l);
void After_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void show_dsVe(PTR_ChuyenBay &p, PTR_HK root, int page_now);
bool check_new_MACB(PTR_ChuyenBay First, char *maCB);

bool check_exist_SHMB(List_MayBay list, char *SHMB);
bool check_SHMB_for_newCB(PTR_ChuyenBay First, List_MayBay listMB, char *SHMB);
void NhapChuyenBay(PTR_ChuyenBay &First, List_MayBay list);
void XuLyCB(PTR_ChuyenBay &p, PTR_HK root);
void XuLyDSChuyenBay(PTR_ChuyenBay &First_CB, PTR_HK root, List_MayBay list);

// Quynh
void FilterList_CB(PTR_ChuyenBay First_CB);
int kiemtra_SHMB_moi(List_MayBay list, char *SHMB);
void XuLyMB(List_MayBay &list, int vitri);
void Insert_MayBay(List_MayBay &list_MB);
void QuanLyMayBay(List_MayBay &list_MB);

//THIN
void DanhSachGheTrong(PTR_ChuyenBay &First_CB, List_MayBay &list_MB);
void DanhSachGheTrongTheoChuyenBay(ChuyenBay p);
void SapXepDanhSachMayBayQuickSort(List_MayBay &list_MB, int vitri_dstk[], int q, int r);
void ThongKeTheoTrang(int current_page, int total_page, List_MayBay &list_MB, int *vitri_dstk);
void ThongKeChuyenBay(List_MayBay &list_MB);

int dem_CB(PTR_ChuyenBay list, string status)
{
	int count = 0;
	PTR_ChuyenBay p;
	if (status == CHUABAY)
	{
		for (p = list; p != NULL; p = p->next)
			if (p->data.trangthai != HOANTAT && p->data.trangthai != HUYCHUYEN)
				count++;
	}
	else if (status == TATCA)
	{
		for (p = list; p != NULL; p = p->next)
			count++;
	}
	return count;
}

void show_List_CB(PTR_ChuyenBay l, int page_now, int count_CB, string status)
{
	int MAXLIST = 10;
	ChuyenBay *temp = new ChuyenBay[count_CB];
	int dem = 0;
	PTR_ChuyenBay p;
	int count_page = (count_CB % MAXLIST == 0) ? (count_CB / MAXLIST) : (count_CB / MAXLIST + 1);
	if (status == CHUABAY)
	{
		for (p = l; p != NULL; p = p->next)
			if (p->data.trangthai != HOANTAT && p->data.trangthai != HUYCHUYEN)
				temp[dem++] = p->data;
	}
	else if (status == TATCA)
	{
		for (p = l; p != NULL; p = p->next)
			temp[dem++] = p->data;
	}
	if (count_CB == 0)
	{
		outtextxy(30, 11, "KHONG CO CHUYEN BAY NAO");
		ShowCur(false);
		delete[] temp;
		return;
	}
	Clear_Frame_Main();
	outtextxy(2, 11, "+------------------+---------------------+---------------------+-----------------------+--------------+");
	outtextxy(2, 12, "|  MA CHUYEN BAY   |   NGAY GIO BAY      |   SO HIEU MAY BAY   |   SAN BAY DEN         | SO GHE TRONG |");
	int y = 11;
	for (int i = 0; i < count_CB; i++)
	{
		if (i < page_now * 10 && i >= (page_now - 1) * 10)
		{
			y += 2;
			outtextxy(2, y, "+------------------+---------------------+---------------------+-----------------------+--------------+");
			outtextxy(2, y + 1, concat("|", temp[i].ma_chuyenbay));
			outtextxy(21, y + 1, concat("|", tocharDate(temp[i].ngaykhoihanh)));
			outtextxy(43, y + 1, concat("|", temp[i].sohieu_maybay));
			outtextxy(65, y + 1, concat("|", temp[i].sanbayden));
			outtextxy(89, y + 1, "|" + intToString(sovechuaban(temp[i])));
			outtextxy(104, y + 1, "|");
		}
		if (i >= (page_now)*10)
			break;
	}
	outtextxy(2, wherey() + 1, "+------------------+---------------------+---------------------+-----------------------+--------------+");
	delete[] temp;
}

PTR_ChuyenBay hanhkhach_chuahoanthanhchuyenbay(PTR_ChuyenBay list_CB, char *CMND)
{
	PTR_ChuyenBay p;
	for (p = list_CB; p != NULL; p = p->next)
		if (p->data.trangthai != HUYCHUYEN && p->data.trangthai != HOANTAT)
			for (int i = 1; i <= p->data.soVe; i++)
			{
				if (p->data.danhsachVe[i] == CMND)
					return p;
			}
	return NULL;
}

PTR_ChuyenBay check_maCB_chuabay(PTR_ChuyenBay list_CB, char *maCB)
{
	PTR_ChuyenBay p;
	for (p = list_CB; p != NULL; p = p->next)
		if (p->data.trangthai != HUYCHUYEN && p->data.trangthai != HOANTAT)
			if (strcmp(maCB, p->data.ma_chuyenbay) == 0)
				return p;
	return NULL;
}

int DatVe(PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{
	Clear_Frame_Main();
	bool is_add_HK = true;
	int page_now = 1;
	int count_CB = dem_CB(First_CB, CHUABAY);
	int count_page = (count_CB % 10 == 0) ? (count_CB / 10) : (count_CB / 10 + 1);
	show_List_CB(First_CB, page_now, count_CB, CHUABAY);
	outtextxy(115, 6, "Ma CB: ");
	outtextxy(115, 8, "CMND: ");
	outtextxy(115, 10, "Ho: ");
	outtextxy(115, 12, "Ten: ");
	outtextxy(115, 14, "Phai: ");
	outtextxy(115, 16, "Ma Ghe: ");
	char key = 0;
	char maCB[MAX_LENGTH_MACB + 1] = "";
	char CMND[MAX_LENGTH_CMND + 1] = "";
	char ho[MAX_LENGTH_HO + 1] = "";
	char ten[MAX_LENGTH_TEN + 1] = "";
	char phai[4] = "";
	int maghe;
	char maghe_str[6] = "";
	ShowCur(true);
	gotoxy(125, 6);
	int run = 1;
	PTR_ChuyenBay p;
	while (run)
	{
		int y = wherey();
		switch (y)
		{
		case 6:
		{
			nhapChuoi(maCB, MAX_LENGTH_MACB, key, NO_SPACE);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			else
			{
				if (key == UP)
				{
					key = 0;
					continue;
				}
				if (key == DOWN || key == ENTER || key == TAB)
				{
					p = check_maCB_chuabay(First_CB, maCB);
					if (p == NULL)
					{
						Show_Message("ERROR", "KHONG TON TAI CHUYEN BAY");
						gotoxy(125 + strlen(maCB), 6);
					}
					else
						gotoxy(125 + strlen(CMND), 8);
					key = 0;
					continue;
				}
				if (key == PAGEUP)
				{
					key = 0;
					if (page_now == 1)
						continue;
					show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(maCB), 6);
					continue;
				}
				if (key == PAGEDOWN)
				{
					key = 0;
					if (page_now == count_page)
						continue;
					show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(maCB), 6);
					continue;
				}
			}
			break;
		}
		case 8:
		{
			nhapChuoi(CMND, MAX_LENGTH_CMND, key, ONLY_NUMBER);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			else
			{
				if (key == UP)
				{
					key = 0;
					gotoxy(125 + strlen(maCB), 6);
					continue;
				}
				if (key == DOWN || key == ENTER || key == TAB)
				{
					if (strlen(CMND) != 9 && strlen(CMND) != 12)
					{
						Show_Message("ERROR", "CMND KHONG HOP LE");
						gotoxy(125 + strlen(CMND), 8);
						key = 0;
						continue;
					}
					PTR_HK hk = timkiem_HK(root_HK, CMND);
					if (hk != NULL)
					{
						is_add_HK = false;
						outtextxy(125, 10, hk->info.ho);
						strcpy(ho, hk->info.ho);
						outtextxy(125, 12, hk->info.ten);
						strcpy(ten, hk->info.ten);
						if (hk->info.phai == 1)
						{
							outtextxy(125, 14, "NAM");
							strcpy(phai, "NAM");
						}
						else
						{
							outtextxy(125, 14, "NU");
							strcpy(phai, "NU");
						}
						if (hanhkhach_chuahoanthanhchuyenbay(First_CB, CMND) != NULL)
						{
							Show_Message("ERROR", "HANH KHACH DANG CO CHUYEN BAY");
							gotoxy(125 + strlen(CMND), 8);
							key = 0;
							continue;
						}
					}
					else
					{
						is_add_HK = true;
					}
					if (!is_add_HK)
						gotoxy(125 + strlen(maghe_str), 16);
					else
						gotoxy(125 + strlen(ho), 10);
					key = 0;
					continue;
				}
				if (key == PAGEUP)
				{
					key = 0;
					if (page_now == 1)
						continue;
					show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(CMND), 8);
					continue;
				}
				if (key == PAGEDOWN)
				{
					key = 0;
					if (page_now == count_page)
						continue;
					show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(CMND), 8);
					continue;
				}
			}
			break;
		}
		case 10:
		{
			nhapChuoi(ho, MAX_LENGTH_HO, key, ONLY_WORD);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			else
			{
				if (key == UP)
				{
					key = 0;
					gotoxy(125 + strlen(CMND), 8);
					continue;
				}
				if (key == DOWN || key == ENTER || key == TAB)
				{
					LTrim(ho);
					RTrim(ho);
					if (strlen(ho) == 0)
					{
						Show_Message("ERROR", "HO KHONG HOP LE");
						gotoxy(125 + strlen(ho), 10);
					}
					else
						gotoxy(125 + strlen(ten), 12);
					key = 0;
					continue;
				}
				if (key == PAGEUP)
				{
					key = 0;
					if (page_now == 1)
						continue;
					show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(ho), 10);
					continue;
				}
				if (key == PAGEDOWN)
				{
					key = 0;
					if (page_now == count_page)
						continue;
					show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(ho), 10);
					continue;
				}
			}
			break;
		}
		case 12:
		{
			nhapChuoi(ten, MAX_LENGTH_TEN, key, ONLY_WORD);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			else
			{
				if (key == UP)
				{
					key = 0;
					gotoxy(125 + strlen(ho), 10);
					continue;
				}
				if (key == DOWN || key == ENTER || key == TAB)
				{
					LTrim(ten);
					RTrim(ten);
					if (strlen(ten) == 0)
					{
						Show_Message("ERROR", "TEN KHONG HOP LE");
						gotoxy(125 + strlen(ten), 12);
					}
					else
						gotoxy(125 + strlen(phai), 14);
					key = 0;
					continue;
				}
				if (key == PAGEUP)
				{
					key = 0;
					if (page_now == 1)
						continue;
					show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(ten), 12);
					continue;
				}
				if (key == PAGEDOWN)
				{
					key = 0;
					if (page_now == count_page)
						continue;
					show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(ten), 12);
					continue;
				}
			}
			break;
		}
		case 14:
		{
			nhapChuoi(phai, 3, key, NO_SPACE);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			else
			{
				if (key == UP)
				{
					key = 0;
					gotoxy(125 + strlen(ten), 12);
					continue;
				}
				if (key == DOWN || key == ENTER || key == TAB)
				{
					if (strcmp(phai, "NAM") != 0 && strcmp(phai, "NU") != 0)
					{
						Show_Message("ERROR", "PHAI KHONG HOP LE");
						gotoxy(125 + strlen(phai), 14);
					}
					else
						gotoxy(125 + strlen(maghe_str), 16);
					key = 0;
					continue;
				}
				if (key == PAGEUP)
				{
					key = 0;
					if (page_now == 1)
						continue;
					show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(phai), 14);
					continue;
				}
				if (key == PAGEDOWN)
				{
					key = 0;
					if (page_now == count_page)
						continue;
					show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
					gotoxy(125 + strlen(phai), 14);
					continue;
				}
			}
			break;
		}
		case 16:
		{
			nhapChuoi(maghe_str, 5, key, ONLY_NUMBER);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			if (key == ENTER)
			{
				maghe = toInt(maghe_str);
				if (maghe <= 0 || maghe > p->data.soVe)
				{
					Show_Message("ERROR", "MA GHE KHONG DUNG");
					gotoxy(125 + strlen(maghe_str), 16);
					key = 0;
					continue;
				}
				if (p->data.danhsachVe[maghe] != "0")
				{
					Show_Message("ERROR", "GHE DA CO NGUOI DANG KI");
					gotoxy(125 + strlen(maghe_str), 16);
					key = 0;
					continue;
				}
				if (is_add_HK)
				{
					p->data.danhsachVe[maghe] = CMND;
					HanhKhach newHK;
					strcpy(newHK.CMND, CMND);
					strcpy(newHK.ho, ho);
					strcpy(newHK.ten, ten);
					if (strcmp(phai, "NAM") == 0)
						newHK.phai = 1;
					else
						newHK.phai = 0;
					Add_HK_to_List(root_HK, newHK);
				}
				else
				{
					p->data.danhsachVe[maghe] = CMND;
				}
				Show_Message("SUCCESS", "MUA VE THANH CONG");
				checkFull_CB(p);
				show_List_CB(First_CB, page_now, count_CB, CHUABAY);
			}
			else
			{
				if (key == UP)
				{
					if (!is_add_HK)
						gotoxy(125 + strlen(CMND), 8);
					else
						gotoxy(125 + strlen(phai), 14);
					key = 0;
					continue;
				}
				if (key == DOWN)
				{
					key = 0;
					continue;
				}
				if (key == PAGEUP)
				{
					key = 0;
					if (page_now == 1)
						continue;
					show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
					gotoxy(125 + intToString(maghe).size(), 16);
					continue;
				}
				if (key == PAGEDOWN)
				{
					key = 0;
					if (page_now == count_page)
						continue;
					show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
					gotoxy(125 + intToString(maghe).size(), 16);
					continue;
				}
			}
			break;
		}
		default:
		{
			gotoxy(125 + strlen(maCB), 6);
		}
		}
	}
}

int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{
	Clear_Frame_Main();
	int page_now = 1;
	int count_CB = dem_CB(First_CB, CHUABAY);
	int count_page = (count_CB % 10 == 0) ? (count_CB / 10) : (count_CB / 10 + 1);
	show_List_CB(First_CB, page_now, count_CB, CHUABAY);
	outtextxy(115, 6, "CMND: ");
	outtextxy(115, 8, "Ho: ");
	outtextxy(115, 10, "Ten: ");
	outtextxy(115, 12, "Phai: ");
	outtextxy(115, 14, "Ma CB: ");
	outtextxy(115, 16, "Ma Ghe: ");
	outtextxy(115, 18, "SB Den: ");
	outtextxy(115, 20, "Time: ");
	char key = 0;
	char CMND[MAX_LENGTH_CMND + 1] = "";
	gotoxy(125, 6);
	PTR_ChuyenBay p;
	int run = 1;
	int soghe = 0;
	while (run)
	{
		int y = wherey();
		ShowCur(true);
		switch (y)
		{
		case 6:
		{
			nhapChuoi(CMND, MAX_LENGTH_CMND, key, ONLY_NUMBER);
			if (key == ESC)
			{
				run = 0;
				key = 0;
				break;
			}
			if (key == ENTER)
			{
				if (strlen(CMND) != 9 && strlen(CMND) != 12)
				{
					Show_Message("ERROR", "CMND KHONG HOP LE");
					gotoxy(125 + strlen(CMND), 6);
					key = 0;
					continue;
				}
				PTR_HK hk = timkiem_HK(root_HK, CMND);
				if (hk != NULL)
				{
					outtextxy(125, 8, hk->info.ho);
					outtextxy(125, 10, hk->info.ten);
					if (hk->info.phai == 1)
						outtextxy(125, 12, "NAM");
					else
						outtextxy(125, 12, "NU");
					PTR_ChuyenBay p = hanhkhach_chuahoanthanhchuyenbay(First_CB, CMND);
					if (p != NULL)
					{
						outtextxy(125, 14, p->data.ma_chuyenbay);
						gotoxy(125, 16);
						cout << "     ";
						gotoxy(125, 16);
						for (int i = 1; i <= p->data.soVe; i++)
							if (p->data.danhsachVe[i] == CMND)
							{
								cout << i;
								soghe = i;
								break;
							}
						outtextxy(125, 18, p->data.sanbayden);
						gotoxy(125, 20);
						cout << "                              ";
						outtextxy(125, 20, tocharDate(p->data.ngaykhoihanh));
						int chon = form_confirm("BAN CO MUON HUY VE KHONG");
						if (chon == -1)
						{
							run = 0;
							key = 0;
							break;
						}
						else if (chon == 1)
						{
							p->data.danhsachVe[soghe] = "0";
							p->data.trangthai = CONVE;
							Show_Message("SUCCESS", "HUY VE THANH CONG");
							show_List_CB(First_CB, page_now, count_CB, CHUABAY);
							outtextxy(125, 14, "");
							outtextxy(125, 16, "");
							outtextxy(125, 18, "");
							outtextxy(125, 20, "");
						}
						else
							break;
					}
					else
					{
						outtextxy(125, 14, "");
						outtextxy(125, 16, "");
						outtextxy(125, 18, "");
						outtextxy(125, 20, "");
						Show_Message("ERROR", "HANH KHACH CHUA DAT VE");
						gotoxy(125 + strlen(CMND), 6);
						key = 0;
						continue;
					}
				}
				else
				{
					outtextxy(125, 8, "");
					outtextxy(125, 10, "");
					outtextxy(125, 12, "");
					outtextxy(125, 14, "");
					outtextxy(125, 16, "");
					outtextxy(125, 18, "");
					outtextxy(125, 20, "");
					Show_Message("ERROR", "HANH KHACH CHUA DAT VE");
					gotoxy(125 + strlen(CMND), 6);
					key = 0;
					continue;
				}
			}
			if (key == PAGEUP)
			{
				key = 0;
				if (page_now == 1)
					continue;
				show_List_CB(First_CB, --page_now, count_CB, CHUABAY);
				gotoxy(125 + strlen(CMND), 6);
				continue;
			}
			if (key == PAGEDOWN)
			{
				key = 0;
				if (page_now == count_page)
					continue;
				show_List_CB(First_CB, ++page_now, count_CB, CHUABAY);
				gotoxy(125 + strlen(CMND), 6);
				continue;
			}
			break;
		}
		default:
		{
			gotoxy(125 + strlen(CMND), 6);
			continue;
			break;
		}
		}
	}
}

void show_dsVe(PTR_ChuyenBay &p, PTR_HK root, int page_now)
{
	int soluongvedaban = p->data.soVe - sovechuaban(p->data);
	int count_page;
	if (soluongvedaban % 10 == 0)
		count_page = soluongvedaban / 10;
	else
		count_page = soluongvedaban / 10 + 1;
	int stt = 0;
	if (soluongvedaban == 0)
	{
		outtextxy(30, 11, "KHONG CO HANH KHACH NAO");
		ShowCur(false);
		return;
	}
	Clear_Frame_Main();
	outtextxy(10, 8, concat("DANH SACH HANH KHACH THUOC CHUYEN BAY ", p->data.ma_chuyenbay));
	outtextxy(10, 9, concat("NGAY GIO KHOI HANH: ", tocharDate(p->data.ngaykhoihanh)));
	outtextxy(50, 9, concat("NOI DEN: ", p->data.sanbayden));
	outtextxy(2, 11, "+--------+-----------+-------------------+------------------------------+--------------+------+");
	outtextxy(2, 12, "|  STT   |   SO VE   |      SO CMND      |            HO                |      TEN     | PHAI |");
	int y = 11;
	for (int i = 1; i <= p->data.soVe; i++)
	{
		if (p->data.danhsachVe[i] != "0")
		{
			++stt;
			if (stt <= page_now * 10)
			{
				if (stt > (page_now - 1) * 10)
				{
					y += 2;
					outtextxy(2, y, "+--------+-----------+-------------------+------------------------------+--------------+------+");
					outtextxy(2, y + 1, "|" + intToString(stt));
					outtextxy(11, y + 1, "|" + intToString(i));
					outtextxy(23, y + 1, "|" + p->data.danhsachVe[i]);
					PTR_HK hk = timkiem_HK(root, p->data.danhsachVe[i].c_str());
					outtextxy(43, y + 1, concat("|", hk->info.ho));
					outtextxy(74, y + 1, concat("|", hk->info.ten));
					if (hk->info.phai == 1)
						outtextxy(89, y + 1, "|NAM");
					else
						outtextxy(89, y + 1, "|NU");
					outtextxy(96, y + 1, "|");
				}
			}
			else
				break;
		}
	}
	outtextxy(2, wherey() + 1, "+--------+-----------+-------------------+------------------------------+--------------+------+");
}

void XuLyCB(PTR_ChuyenBay &p, PTR_HK root)
{
	Clear_Frame_Main();
	int soluongvedaban = p->data.soVe - sovechuaban(p->data);
	int count_page;
	if (soluongvedaban % 10 == 0)
		count_page = soluongvedaban / 10;
	else
		count_page = soluongvedaban / 10 + 1;
	int page_now = 1;
	show_dsVe(p, root, page_now);
	char input;
	int run = 1;
	while (run)
	{
		input = getch();
		switch (input)
		{
		case ENTER:
			break;
		case ESC:
		{
			run = 0;
			break;
		}
		case is_press_arrow_key:
		{
			input = getch();
			if (input == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_dsVe(p, root, --page_now);
			}
			else if (input == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_dsVe(p, root, ++page_now);
			}
			else if (input == BUTTON_DELETE)
			{
				int chon = form_confirm("BAN CO MUON HUY CHUYEN BAY");
				if (chon == -1)
				{
					run = 0;
					break;
				}
				else if (chon == 1)
				{
					if (p->data.trangthai == HOANTAT || p->data.trangthai == HUYCHUYEN)
					{
						Show_Message("ERROR", "KHONG THE HUY CHUYEN BAY NAY");
					}
					else
					{
						p->data.trangthai = HUYCHUYEN;

						outtextxy(125, 14, "HUY CHUYEN");
						Show_Message("SUCCESS", "HUY CHUYEN BAY THANH CONG");
					}
				}
				else if (chon == 0)
				{
					break;
				}
			}
			break;
		}
		case is_press_f:
		{
			input = getch();
			if (input == F4)
			{
				if (p->data.trangthai == HOANTAT || p->data.trangthai == HUYCHUYEN)
					Show_Message("ERROR", "KHONG THE HIEU CHINH");
				else
				{
					int run1 = 1;
					char key1 = 0;
					char date[17] = "";
					strcpy(date, tocharDate(p->data.ngaykhoihanh));
					while (run1)
					{
						gotoxy(125 + strlen(date), 10);
						input_date(date, key1, FULL_DATETIME);
						if (key1 == ENTER)
						{
							if (strlen(date) != 16 || TGTL(charToDay(date, FULL_DATETIME)) == false)
								Show_Message("ERROR", "THOI GIAN KHONG HOP LE");
							else
							{
								p->data.ngaykhoihanh = charToDay(date, FULL_DATETIME);
								Show_Message("SUCCESS", "HIEU CHINH THANH CONG");
								run = 0;
								run1 = 0;
							}
						}
						else if (key1 == ESC)
						{
							outtextxy(125, 10, tocharDate(p->data.ngaykhoihanh));
							ShowCur(false);
							run1 = 0;
							run = 0;
						}
						key1 = 0;
					}
				}
			}
			break;
		}
		}
	}
}

bool check_new_MACB(PTR_ChuyenBay First, char *maCB)
{
	Trim(maCB);
	if (strlen(maCB) == 0)
		return false;
	PTR_ChuyenBay p;
	for (p = First; p != NULL; p = p->next)
		if (strcmp(p->data.ma_chuyenbay, maCB) == 0)
			return false;
	return true;
}

bool check_exist_SHMB(List_MayBay list, char *SHMB)
{
	for (int i = 0; i < list.soluong; i++)
		if (strcmp(list.nodes[i]->sohieu_maybay, SHMB) == 0)
			return true;
	return false;
}

bool check_SHMB_for_newCB(PTR_ChuyenBay First, List_MayBay listMB, char *SHMB)
{
	PTR_ChuyenBay cb;
	if (!check_exist_SHMB(listMB, SHMB))
		return false;
	for (cb = First; cb != NULL; cb = cb->next)
		if (strcmp(cb->data.sohieu_maybay, SHMB) == 0 && (cb->data.trangthai != HUYCHUYEN) && (cb->data.trangthai != HOANTAT))
			return false;
	return true;
}

void NhapChuyenBay(PTR_ChuyenBay &First, List_MayBay list)
{
	int page_now = 1;
	int count_CB = dem_CB(First, TATCA);
	int count_page = (count_CB % 10 == 0) ? (count_CB / 10) : (count_CB / 10 + 1);
	show_List_CB(First, page_now, count_CB, TATCA);
	ChuyenBay ret;
	char ma_chuyenbay[MAX_LENGTH_MACB + 1] = "";
	char SHMB[MAX_LENGTH_SHMB + 1] = "";
	char sanbayden[MAX_LENGTH_SBD + 1] = "";
	ret.ngaykhoihanh = Time_now();
	char date[17];
	strcpy(date, tocharDate(ret.ngaykhoihanh));
	outtextxy(125, 6, ma_chuyenbay);
	outtextxy(125, 8, sanbayden);
	outtextxy(125, 10, date);
	outtextxy(125, 12, SHMB);
	outtextxy(125, 14, "CON VE");
	gotoxy(125 + strlen(ma_chuyenbay), 6);
	int run = 1;
	char key = 0;
	while (run)
	{
		int y = wherey();
		ShowCur(true);
		switch (y)
		{
		case 6:
		{
			nhapChuoi(ma_chuyenbay, MAX_LENGTH_MACB, key, NO_SPACE);
			if (key == ENTER || key == TAB || key == DOWN)
			{
				if (!check_new_MACB(First, ma_chuyenbay))
				{
					Show_Message("ERROR", "MA CB KHONG HOP LE");
					gotoxy(125 + strlen(ma_chuyenbay), 6);
					key = 0;
				}
				else
					gotoxy(125 + strlen(sanbayden), 8);
			}
			else if (key == ESC)
			{
				run = key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_CB(First, --page_now, count_CB, TATCA);
				gotoxy(125 + strlen(ma_chuyenbay), 6);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_CB(First, ++page_now, count_CB, TATCA);
				gotoxy(125 + strlen(ma_chuyenbay), 6);
				break;
			}
			break;
		}
		case 8:
		{
			nhapChuoi(sanbayden, MAX_LENGTH_SBD, key, ONLY_WORD);
			if (key == ENTER || key == TAB || key == DOWN)
			{
				LTrim(sanbayden);
				RTrim(sanbayden);
				if (strlen(sanbayden) == 0)
				{
					Show_Message("ERROR", "SAN BAY DEN KHONG HOP LE");
					gotoxy(125 + strlen(sanbayden), 8);
				}
				else
					gotoxy(125 + strlen(date), 10);
				key = 0;
			}
			else if (key == ESC)
				run = key = 0;
			else if (key == UP)
			{
				gotoxy(125 + strlen(ma_chuyenbay), 6);
				key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_CB(First, --page_now, count_CB, TATCA);
				gotoxy(125 + strlen(sanbayden), 8);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_CB(First, ++page_now, count_CB, TATCA);
				gotoxy(125 + strlen(sanbayden), 8);
				break;
			}
			break;
		}
		case 10:
		{
			input_date(date, key, FULL_DATETIME);
			if (key == ENTER || key == TAB || key == DOWN)
			{
				if (strlen(date) != 16)
				{
					Show_Message("ERROR", "FORMAT THOI GIAN KHONG DUNG");
					gotoxy(125 + strlen(date), 10);
				}
				else
				{
					ret.ngaykhoihanh = charToDay(date, FULL_DATETIME);
					if (!TGTL(ret.ngaykhoihanh))
					{
						Show_Message("ERROR", "THOI GIAN KHONG HOP LE");
						gotoxy(125 + strlen(date), 10);
					}
					else
						gotoxy(125 + strlen(SHMB), 12);
				}
				key = 0;
			}
			else if (key == ESC)
				run = key = 0;
			else if (key == UP)
			{
				gotoxy(125 + strlen(sanbayden), 8);
				key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_CB(First, --page_now, count_CB, TATCA);
				gotoxy(125 + strlen(date), 10);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_CB(First, ++page_now, count_CB, TATCA);
				gotoxy(125 + strlen(date), 10);
				break;
			}
			break;
		}
		case 12:
		{
			nhapChuoi(SHMB, MAX_LENGTH_SHMB, key, NO_SPACE);
			if (key == ENTER)
			{
				if (!check_SHMB_for_newCB(First, list, SHMB))
				{
					Show_Message("ERROR", "SHMB KHONG HOP LE");
					gotoxy(125 + strlen(SHMB), 12);
				}
				else
				{
					strcpy(ret.ma_chuyenbay, ma_chuyenbay);
					strcpy(ret.sanbayden, sanbayden);
					strcpy(ret.sohieu_maybay, SHMB);
					InsertOrder_CB(list, First, ret);
					Show_Message("SUCCESS", "THEM CHUYEN BAY THANH CONG");
					run = 0;
				}
			}
			else if (key == ESC)
				run = key = 0;
			else if (key == UP)
			{
				gotoxy(125 + strlen(date), 10);
				key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_CB(First, --page_now, count_CB, TATCA);
				gotoxy(125 + strlen(SHMB), 12);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_CB(First, ++page_now, count_CB, TATCA);
				gotoxy(125 + strlen(SHMB), 12);
				break;
			}
			break;
		}
		}
	}
}

void FilterList_CB(PTR_ChuyenBay First_CB)
{
	Clear_Frame_Input();
	outtextxy(115, 6, "NGAY: ");
	outtextxy(115, 8, "SB DEN: ");
	char key = 0;
	char date[11] = "";
	char SBD[MAX_LENGTH_SBD + 1] = "";
	gotoxy(125, 6);
	Day_time begin, end;
	int run = 1;
	PTR_ChuyenBay p;
	while (run)
	{
		int y = wherey();
		switch (y)
		{
		case 6:
		{
			input_date(date, key, ONLY_DATE);
			if (key == ESC)
				run = 0;
			else if (key == ENTER || key == TAB || key == DOWN)
			{
				if (strlen(date) != 10)
				{
					Show_Message("ERROR", "FORMAT THOI GIAN KHONG HOP LE");
					gotoxy(125 + strlen(date), 6);
				}
				else
				{
					begin = charToDay(date, ONLY_DATE);
					if (!kt(begin))
					{
						Show_Message("ERROR", "THOI GIAN KHONG HOP LE");
						gotoxy(125 + strlen(date), 6);
					}
					else
					{
						end = begin;
						end.gio = 23;
						end.phut = 59;
						gotoxy(125 + strlen(SBD), 8);
					}
				}
			}
			break;
		}
		case 8:
		{
			nhapChuoi(SBD, MAX_LENGTH_SBD, key, ONLY_WORD);
			if (key == ESC)
				run = 0;
			else if (key == ENTER)
			{
				int soluong = 0;
				ChuyenBay temp[dem_CB(First_CB, CHUABAY)];
				for (p = First_CB; p != NULL; p = p->next)
				{
					if (p->data.trangthai == CONVE && strcmp(p->data.sanbayden, SBD) == 0 &&
						(sosanhTG(p->data.ngaykhoihanh, begin) >= 0 && sosanhTG(p->data.ngaykhoihanh, end) <= 0))
					{
						temp[soluong++] = p->data;
					}
				}
				int count_page = (soluong % 10 == 0) ? (soluong / 10) : (soluong / 10 + 1);
				int page_now = 1;
				char input;
				do
				{
					Clear_Frame_Main();
					if (soluong == 0)
					{
						outtextxy(30, 11, "KHONG CO CHUYEN BAY NAO CHUA HOAN THANH");
						ShowCur(false);
					}
					else
					{
						outtextxy(2, 11, "+------------------+---------------------+---------------------+-----------------------+--------------+");
						outtextxy(2, 12, "|  MA CHUYEN BAY   |   NGAY GIO BAY      |   SO HIEU MAY BAY   |   SAN BAY DEN         | SO GHE TRONG |");
						int y = 11;
						for (int i = 0; i < soluong; i++)
						{
							if (i < page_now * 10 && i >= (page_now - 1) * 10)
							{
								y += 2;
								outtextxy(2, y, "+------------------+---------------------+---------------------+-----------------------+--------------+");
								outtextxy(2, y + 1, concat("|", temp[i].ma_chuyenbay));
								outtextxy(21, y + 1, concat("|", tocharDate(temp[i].ngaykhoihanh)));
								outtextxy(43, y + 1, concat("|", temp[i].sohieu_maybay));
								outtextxy(65, y + 1, concat("|", temp[i].sanbayden));
								outtextxy(89, y + 1, "|" + intToString(sovechuaban(temp[i])));
								outtextxy(104, y + 1, "|");
							}
							if (i >= (page_now)*10)
								break;
						}
						outtextxy(2, wherey() + 1, "+------------------+---------------------+---------------------+-----------------------+--------------+");
					}
					input = getch();
					if (input == is_press_arrow_key)
					{
						input = getch();
						if (input == PAGEUP)
						{
							if (page_now == 1)
								continue;
							--page_now;
						}
						else if (input == PAGEDOWN)
						{
							if (page_now == count_page)
								continue;
							++page_now;
						}
					}
					else if (input == ESC)
						break;
				} while (1);
				run = 0;
			}
			else if (key == UP)
			{
				gotoxy(125 + strlen(date), 6);
			}
		}
		}
	}
}

void XuLyDSChuyenBay(PTR_ChuyenBay &First_CB, PTR_HK root, List_MayBay list)
{
	Clear_Frame_Main();
	int page_now = 1;
	int count_CB = dem_CB(First_CB, TATCA);
	int count_page = (count_CB % 10 == 0) ? (count_CB / 10) : (count_CB / 10 + 1);
	show_List_CB(First_CB, page_now, count_CB, TATCA);
	outtextxy(115, 6, "MA CB: ");
	outtextxy(115, 8, "SB DEN: ");
	outtextxy(115, 10, "Time: ");
	outtextxy(115, 12, "SHMB: ");
	outtextxy(115, 14, "Status: ");
	char key = 0;
	char MaCB[MAX_LENGTH_MACB + 1] = "";
	gotoxy(125, 6);
	int run = 1;
	PTR_ChuyenBay p;
	while (run)
	{
		ShowCur(true);
		gotoxy(125 + strlen(MaCB), 6);
		nhapChuoi(MaCB, MAX_LENGTH_MACB, key, NO_SPACE);
		switch (key)
		{
		case ENTER:
		{
			p = timcb_MACB(First_CB, MaCB);
			if (p == NULL)
				Show_Message("ERROR", "KHONG TIM THAY CHUYEN BAY");
			else
			{
				outtextxy(125, 8, p->data.sanbayden);
				outtextxy(125, 10, "");
				outtextxy(125, 10, tocharDate(p->data.ngaykhoihanh));
				outtextxy(125, 12, p->data.sohieu_maybay);
				if (p->data.trangthai == HUYCHUYEN)
					outtextxy(125, 14, "HUY CHUYEN");
				else if (p->data.trangthai == HOANTAT)
					outtextxy(125, 14, "HOAN TAT");
				else if (p->data.trangthai == CONVE)
					outtextxy(125, 14, "CON VE");
				else if (p->data.trangthai == HETVE)
					outtextxy(125, 14, "HET VE");
				XuLyCB(p, root);
				sort_CB(First_CB);
				show_List_CB(First_CB, page_now, count_CB, TATCA);
			}
			break;
		}
		// quynh
		case Ctrl_F:
		{
			Clear_Frame_Main();
			FilterList_CB(First_CB);
			Clear_Frame_Input();
			show_List_CB(First_CB, page_now, count_CB, TATCA);
			outtextxy(115, 6, "MA CB: ");
			outtextxy(125, 6, MaCB);
			outtextxy(115, 8, "SB DEN: ");
			outtextxy(115, 10, "Time: ");
			outtextxy(115, 12, "SHMB: ");
			outtextxy(115, 14, "Status: ");
			break;
		}
		case ESC:
		{
			key = 0;
			run = 0;
			break;
		}
		case INSERT:
		{
			NhapChuyenBay(First_CB, list);
			page_now = 1;
			count_CB  = dem_CB(First_CB, TATCA);
			count_page = (count_CB % 10 == 0) ? (count_CB / 10) : (count_CB / 10 + 1);
			show_List_CB(First_CB, page_now, count_CB, TATCA);
			outtextxy(125, 6, MaCB);
			outtextxy(125, 8, "");
			outtextxy(125, 10, "");
			outtextxy(125, 12, "");
			outtextxy(125, 14, "");
			break;
		}
		case PAGEUP:
		{
			if (page_now == 1)
				continue;
			show_List_CB(First_CB, --page_now, count_CB, TATCA);
			break;
		}
		case PAGEDOWN:
		{
			if (page_now == count_page)
				continue;
			show_List_CB(First_CB, ++page_now, count_CB, TATCA);
			break;
		}
		}
	}
}

void Init_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{
	int x = 4;
	resizeConsole(1300, 760);
	DisableResizeWindow();
	Remove_Scrollbars();
	DisableCtrButton(0, 1, 1);
	ShowCur(false);
	Frame_Drawing(0, height, 0, width);
	Draw_A_Horizontal_Line(height - 4, 0, width);
	Draw_A_Vertical_Line(width_title, 0, height - 4);
	Draw_A_Horizontal_Line(height_title, 0, width_title);
	Draw_Name_Project();
	Draw_Button("ESC:THOAT", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("ENTER:CHON", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("UP:LEN", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("DOWN:XUONG", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("PAGEUP:TRANG TRUOC", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("PAGEDOWN:TRANG SAU", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("INSERT:THEM", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("DELETE:XOA", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("CTRL+F:TIM KIEM", x, height - 3, 7);
	x = wherex() + 2;
	Draw_Button("F4:CHINH SUA", x, height - 3, 7);
	Read_File(list_MB, First_CB, root_HK);
}

void show_List_MB(List_MayBay list, int page_now)
{
	int count_page;
	if (list.soluong % 10 == 0)
		count_page = list.soluong / 10;
	else
		count_page = list.soluong / 10 + 1;
	if (list.soluong == 0)
	{
		outtextxy(30, 11, "KHONG CO MAY BAY NAO");
		ShowCur(false);
		return;
	}
	Clear_Frame_Main();
	outtextxy(2, 11, "+--------+--------------------+---------------------------------------------+--------------+");
	outtextxy(2, 12, "|  STT   |     SO HIEU MB     |                 LOAI MAY BAY                |     SO CHO   |");
	int y = 11;
	for (int i = 0; i < list.soluong; i++)
	{
		if (i < page_now * 10 && i >= (page_now - 1) * 10)
		{
			y += 2;
			outtextxy(2, y, "+--------+--------------------+---------------------------------------------+--------------+");
			outtextxy(2, y + 1, "|" + intToString(i + 1));
			outtextxy(11, y + 1, concat("|", list.nodes[i]->sohieu_maybay));
			outtextxy(32, y + 1, concat("|", list.nodes[i]->loai_maybay));
			outtextxy(78, y + 1, "|" + intToString(list.nodes[i]->socho));
			outtextxy(93, y + 1, "|");
		}
		if (i >= (page_now)*10)
			break;
	}
	outtextxy(2, wherey() + 1, "+--------+--------------------+---------------------------------------------+--------------+");
}

void Deletedequi(PTR_HK &root_HK)
{
	if (root_HK != NULL)
	{
		Deletedequi(root_HK->left);
		Deletedequi(root_HK->right);
		delete root_HK;
	}
}

void deleteListCB(PTR_ChuyenBay &First)
{
	while (First != NULL)
	{
		PTR_ChuyenBay temp = First;
		First = First->next;
		delete[] temp->data.danhsachVe;
		delete temp;
	}
}

void deleteListMB(List_MayBay &l)
{
	for (int i = 0; i < l.soluong; i++)
	{
		if (l.nodes[i] == NULL)
			break;
		delete l.nodes[i];
	}
}

void After_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{
	Write_File(list_MB, First_CB, root_HK);
	deleteListMB(list_MB);
	deleteListCB(First_CB);
	Deletedequi(root_HK);
	Clear_Frame_Main();
	Clear_Frame_Input();
	Draw_GoodBye();
}

int SelectLV1()
{
	string listMenu[2] = {" QUAN LY MAY BAY  ", "QUAN LY CHUYEN BAY"};
	for (int i = 0; i < 2; i++)
		Draw_Button(listMenu[i], 40, 15 + i * 4, 7);
	int key = 0;
	Draw_Button(listMenu[key], 40, 15, 6);
	char input;
	while (1)
	{
		input = getch();
		if (input == ENTER)
			break;
		if (input == ESC)
			return -1;
		if (input == is_press_arrow_key)
		{
			input = getch();
			if (input == UP && key != 0)
			{
				Draw_Button(listMenu[key], 40, 15 + key * 4, 7);
				--key;
				Draw_Button(listMenu[key], 40, 15, 6);
				continue;
			}
			else if (input == DOWN && key != 1)
			{
				Draw_Button(listMenu[key], 40, 15, 7);
				++key;
				Draw_Button(listMenu[key], 40, 15 + key * 4, 6);
				continue;
			}
			else
				continue;
		}
	}
	return key;
}

int SelectLV2_1()
{
	Clear_Frame_Main();
	Clear_Frame_Input();
	string listMenu_1[1] = {"DANH SACH MAY BAY"};
	for (int i = 0; i < 1; i++)
		Draw_Button(listMenu_1[i], 40, 15 + i * 4, 7);
	int key = 0;
	Draw_Button(listMenu_1[0], 40, 15, 6);
	char input;
	while (1)
	{
		input = getch();
		if (input == ENTER)
			break;
		if (input == ESC)
			return -1;
		if (input == is_press_arrow_key)
		{
			input = getch();
			if (input == UP && key != 0)
			{
				Draw_Button(listMenu_1[key], 40, 15 + 4 * key, 7);
				--key;
				Draw_Button(listMenu_1[key], 40, 15 + 4 * key, 6);
				continue;
			}
			else if (input == DOWN && key != 0)
			{
				Draw_Button(listMenu_1[key], 40, 15 + 4 * key, 7);
				++key;
				Draw_Button(listMenu_1[key], 40, 15 + 4 * key, 6);
				continue;
			}
			else
				continue;
		}
	}
	return key;
}

int SelectLV2_2()
{
	Clear_Frame_Main();
	Clear_Frame_Input();
	string listMenu_2[5] = {" DANH SACH CHUYEN BAY ",
							"        DAT VE        ",
							"        HUY VE        ",
							"  DANH SACH GHE TRONG ",
							"THONG KE SO CHUYEN BAY"};
	for (int i = 0; i < 5; i++)
		Draw_Button(listMenu_2[i], 40, 15 + i * 4, 7);
	int key = 0;
	Draw_Button(listMenu_2[key], 40, 15 + 4 * key, 6);
	char input;
	while (1)
	{
		input = getch();
		if (input == ENTER)
			break;
		if (input == ESC)
			return -1;
		if (input == is_press_arrow_key)
		{
			input = getch();
			if (input == UP && key != 0)
			{
				Draw_Button(listMenu_2[key], 40, 15 + 4 * key, 7);
				--key;
				Draw_Button(listMenu_2[key], 40, 15 + 4 * key, 6);
				continue;
			}
			else if (input == DOWN && key != 4)
			{
				Draw_Button(listMenu_2[key], 40, 15 + 4 * key, 7);
				++key;
				Draw_Button(listMenu_2[key], 40, 15 + 4 * key, 6);
				continue;
			}
			else
				continue;
		}
	}
	return key;
}

void XuLyMB(List_MayBay &list, int vitri)
{
	MayBay *temp = list.nodes[vitri];
	char input;
	int run = 1;
	while (run)
	{
		input = getch();
		switch (input)
		{
		case ENTER:
			break;
		case ESC:
		{
			run = 0;
			break;
		}
		case is_press_arrow_key:
		{
			input = getch();
			if (input == BUTTON_DELETE)
			{
				int chon = form_confirm("BAN CO MUON XOA MAY BAY");
				if (chon == -1)
				{
					run = 0;
					break;
				}
				else if (chon == 1)
				{
					if (temp->sochuyendabay != 0)
					{
						Show_Message("ERROR", "KHONG THE XOA MAY BAY");
					}
					else
					{
						if (!xoa_mb_khoids(list, vitri))
							Show_Message("ERROR", "XOA THAT BAI");
						else
							Show_Message("SUCCESS", "XOA MAY BAY THANH CONG");
						run = 0;
					}
				}
				else if (chon == 0)
				{
					break;
				}
			}
			break;
		}
		case is_press_f:
		{
			input = getch();
			if (input == F4)
			{
				int run1 = 1;
				char key1 = 0;
				char loaiMB[MAX_LENGTH_LOAIMB + 1] = "";
				strcpy(loaiMB, temp->loai_maybay);
				while (run1)
				{
					gotoxy(125 + strlen(loaiMB), 8);
					nhapChuoi(loaiMB, MAX_LENGTH_LOAIMB, key1, ONLY_WORD);
					if (key1 == ENTER)
					{
						LTrim(loaiMB);
						RTrim(loaiMB);
						if (strlen(loaiMB) == 0)
						{
							Show_Message("ERROR", "LOAI MAY BAY KHONG HOP LE");
							gotoxy(125 + strlen(loaiMB), 8);
							continue;
						}
						else
						{
							strcpy(temp->loai_maybay, loaiMB);
							Show_Message("SUCCESS", "CHINH SUA THANH CONG");
							outtextxy(125, 8, temp->loai_maybay);
							run1 = 0;
							run = 0;
						}
					}
					else if (key1 == ESC)
					{
						outtextxy(125, 8, temp->loai_maybay);
						ShowCur(false);
						run1 = 0;
						run = 0;
					}
					key1 = 0;
				}
			}
			break;
		}
		}
	}
}

int kiemtra_SHMB_moi(List_MayBay list, char *SHMB)
{
	LTrim(SHMB);
	RTrim(SHMB);
	if (strlen(SHMB) == 0)
		return -1;
	for (int i = 0; i < list.soluong; i++)
		if (strcmp(list.nodes[i]->sohieu_maybay, SHMB) == 0)
			return 0;
	return 1;
}

void Insert_MayBay(List_MayBay &list_MB)
{
	int page_now = 1;
	int count_page = (list_MB.soluong % 10 == 0) ? (list_MB.soluong / 10) : (list_MB.soluong / 10 + 1);
	show_List_MB(list_MB, page_now);
	MayBay temp;
	char SHMB[MAX_LENGTH_SHMB + 1] = "";
	char LoaiMB[MAX_LENGTH_LOAIMB + 1] = "";
	char socho[6] = "";
	outtextxy(125, 6, SHMB);
	outtextxy(125, 8, LoaiMB);
	outtextxy(125, 10, socho);
	outtextxy(125, 12, "0");
	gotoxy(125 + strlen(SHMB), 6);
	int run = 1;
	char key = 0;
	while (run)
	{
		int y = wherey();
		ShowCur(true);
		switch (y)
		{
		case 6:
		{
			nhapChuoi(SHMB, MAX_LENGTH_SHMB, key, NO_SPACE);
			if (key == ENTER || key == TAB || key == DOWN)
			{
				if (kiemtra_SHMB_moi(list_MB, SHMB) == -1)
				{
					Show_Message("ERROR", "MA CB KHONG HOP LE");
					gotoxy(125 + strlen(SHMB), 6);
					key = 0;
				}
				else if (kiemtra_SHMB_moi(list_MB, SHMB) == 0)
				{
					Show_Message("ERROR", "MA CB DA TON TAI");
					gotoxy(125 + strlen(SHMB), 6);
					key = 0;
				}
				else
					gotoxy(125 + strlen(LoaiMB), 8);
			}
			else if (key == ESC)
			{
				run = key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_MB(list_MB, --page_now);
				gotoxy(125 + strlen(SHMB), 6);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_MB(list_MB, ++page_now);
				gotoxy(125 + strlen(SHMB), 6);
				break;
			}
			break;
		}
		case 8:
		{
			nhapChuoi(LoaiMB, MAX_LENGTH_LOAIMB, key, ONLY_WORD);
			if (key == ENTER || key == TAB || key == DOWN)
			{
				LTrim(LoaiMB);
				RTrim(LoaiMB);
				if (strlen(LoaiMB) == 0)
				{
					Show_Message("ERROR", "LOAI MAY BAY KHONG HOP LE");
					gotoxy(125 + strlen(LoaiMB), 8);
				}
				else
					gotoxy(125 + strlen(socho), 10);
				key = 0;
			}
			else if (key == ESC)
				run = key = 0;
			else if (key == UP)
			{
				gotoxy(125 + strlen(SHMB), 6);
				key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_MB(list_MB, --page_now);
				gotoxy(125 + strlen(LoaiMB), 8);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_MB(list_MB, ++page_now);
				gotoxy(125 + strlen(LoaiMB), 8);
				break;
			}
			break;
		}
		case 10:
		{
			nhapChuoi(socho, 5, key, ONLY_NUMBER);
			if (key == ENTER)
			{
				int socho_int = toInt(socho);
				if (socho_int <= 0)
				{
					Show_Message("ERROR", "SO CHO KHONG HOP LE");
					gotoxy(125 + strlen(socho), 10);
				}
				else
				{
					strcpy(temp.sohieu_maybay, SHMB);
					strcpy(temp.loai_maybay, LoaiMB);
					temp.socho = socho_int;
					temp.sochuyendabay = 0;
					int k = Add_MB_to_List(list_MB, temp);
					if (k == 0)
					{
						Show_Message("ERROR", "DANH SACH DAY");
						gotoxy(125 + strlen(socho), 10);
					}
					else
					{
						Show_Message("SUCCESS", "THEM MAY BAY THANH CONG");
						run = 0;
					}
				}
				key = 0;
			}
			else if (key == ESC)
				run = key = 0;
			else if (key == UP)
			{
				gotoxy(125 + strlen(LoaiMB), 8);
				key = 0;
			}
			else if (key == PAGEUP)
			{
				if (page_now == 1)
					continue;
				show_List_MB(list_MB, --page_now);
				gotoxy(125 + strlen(socho), 10);
				break;
			}
			else if (key == PAGEDOWN)
			{
				if (page_now == count_page)
					continue;
				show_List_MB(list_MB, ++page_now);
				gotoxy(125 + strlen(socho), 10);
				break;
			}
			break;
		}
		}
	}
}

void QuanLyMayBay(List_MayBay &list_MB)
{
	Clear_Frame_Main();
	int page_now = 1;
	int count_page = (list_MB.soluong % 10 == 0) ? (list_MB.soluong / 10) : (list_MB.soluong / 10 + 1);
	show_List_MB(list_MB, page_now);
	int run = 1;
	char key = 0;
	outtextxy(115, 6, "SHMB: ");
	outtextxy(115, 8, "LOAI MB: ");
	outtextxy(115, 10, "So Cho: ");
	outtextxy(115, 12, "So CDB: ");
	char SHMB[MAX_LENGTH_SHMB + 1] = "";
	while (run)
	{
		gotoxy(125 + strlen(SHMB), 6);
		nhapChuoi(SHMB, MAX_LENGTH_SHMB, key, NO_SPACE);
		switch (key)
		{
		case ENTER:
		{
			int vitri = timkiem_MB(list_MB, SHMB);
			if (vitri == -1)
				Show_Message("ERROR", "KHONG TIM THAY MAY BAY");
			else
			{
				outtextxy(125, 6, list_MB.nodes[vitri]->sohieu_maybay);
				outtextxy(125, 8, list_MB.nodes[vitri]->loai_maybay);
				outtextxy(125, 10, intToString(list_MB.nodes[vitri]->socho));
				outtextxy(125, 12, intToString(list_MB.nodes[vitri]->sochuyendabay));
				XuLyMB(list_MB, vitri);
				page_now = 1;
				count_page = (list_MB.soluong % 10 == 0) ? (list_MB.soluong / 10) : (list_MB.soluong / 10 + 1);
				show_List_MB(list_MB, page_now);
			}
			break;
		}
		case PAGEUP:
		{
			if (page_now == 1)
				continue;
			show_List_MB(list_MB, --page_now);
			break;
		}
		case PAGEDOWN:
		{
			if (page_now == count_page)
				continue;
			show_List_MB(list_MB, ++page_now);
			break;
		}
		case INSERT:
		{
			Insert_MayBay(list_MB);
			page_now = 1;
			count_page = (list_MB.soluong % 10 == 0) ? (list_MB.soluong / 10) : (list_MB.soluong / 10 + 1);
			show_List_MB(list_MB, page_now);
			outtextxy(125, 6, SHMB);
			outtextxy(125, 8, "");
			outtextxy(125, 10, "");
			outtextxy(125, 12, "");
			break;
		}
		case ESC:
		{
			key = 0;
			run = 0;
			break;
		}
		}
	}
}
void DanhSachGheTrong(PTR_ChuyenBay &First_CB, List_MayBay &list_MB)
{
	Clear_Frame_Input();
	Clear_Frame_Main();
	int currentPage = 1;
	int count_CB = dem_CB(First_CB, TATCA);
	int totalPage = (count_CB % 10 == 0) ? (count_CB / 10) : (count_CB / 10 + 1);
	show_List_CB(First_CB, currentPage, count_CB, TATCA);
	outtextxy(115,6,"Nhap Ma Chuyen Bay:");
	char key = 0;
	char MaCB[MAX_LENGTH_MACB + 1] = "";
	int run = 1;
	PTR_ChuyenBay p;
	while (run)
	{
		ShowCur(true);
		gotoxy(134 + strlen(MaCB), 6);
		nhapChuoi(MaCB, MAX_LENGTH_MACB, key, NO_SPACE);
		switch (key)
		{
		case ENTER:
		{
			p = timcb_MACB(First_CB, MaCB);
			if (p == NULL)
			{
				Show_Message("ERROR", "KHONG TIM THAY CHUYEN BAY");
				run = 1;
				continue;
			}
			else
			{
				Clear_Frame_Main();
				outtextxy(25, 7, "+--------------------------------------------------------------+");
				outtextxy(25, 8, "|                      DANH SACH GHE TRONG                     |");
				outtextxy(25, 9, "+--------------------------------------------------------------+");
				SetBGColor(6);
				outtextxy(30, 11, "Mau vang: Da duoc dat ve");
				SetBGColor(7);
				SetColor(0);
				outtextxy(60, 11, "Mau trang: Chua dat ve");
				SetBGColor(0);
				DanhSachGheTrongTheoChuyenBay(p->data);
				key = getch();
				if (key == ESC)
				{
					show_List_CB(First_CB, currentPage, count_CB, TATCA);
					run = 1;
//					continue;
				}
			}
			continue;
		}
		case ESC:
		{
			key = 0;
			run = 0;
			continue;
		}
		case Ctrl_F:
		{
			gotoxy(131 + strlen(MaCB), 6);
			run = 1;
			continue;
		}
		case PAGEUP:
		{
			if (currentPage == 1)
				continue;
			show_List_CB(First_CB, --currentPage, count_CB, TATCA);
			break;
		}
		case PAGEDOWN:
		{
			if (currentPage == totalPage)
				continue;
			show_List_CB(First_CB, ++currentPage, count_CB, TATCA);
			break;
		}
		}
	}
}
void DanhSachGheTrongTheoChuyenBay(ChuyenBay p)
{
	int soPhanTuMotHang = 10;
	int tongSoPhanTu = p.soVe;
	int vitri = 0;
	int soHang = tongSoPhanTu / soPhanTuMotHang + 1;
	int hangCuoi = tongSoPhanTu % soPhanTuMotHang;
	if (hangCuoi == 0)
	{
		soHang--;
		for (int i = 0; i < soHang; i++)
		{
			for (int j = 1; j <= soPhanTuMotHang; j++)
			{
				vitri = j + soPhanTuMotHang * i;
				gotoxy(5 + j * 9, 11 + (i + 1) * 2);
				if (p.danhsachVe[vitri] != "0")
				{
					SetColor(6); // ghe da co nguoi ngoi
					cout << vitri;
					continue;
				}
				SetColor(7); // ghe chua co nguoi ngoi
				cout << vitri;
			}
		}
	}
	else
	{
		for (int i = 0; i < soHang - 1; i++)
		{
			for (int j = 1; j <= soPhanTuMotHang; j++)
			{
				vitri = j + i * soPhanTuMotHang;
				gotoxy(5 + j * 9, 11 + (i + 1) * 2);
				if (p.danhsachVe[vitri] != "0")
				{
					SetColor(6); // ghe da co nguoi ngoi
					cout << vitri;
					continue;
				}
				SetColor(7); // ghe chua co nguoi ngoi
				cout << vitri;
			}
		}
		for (int i = 1; i <= hangCuoi; i++)
		{
			vitri = i + (soHang - 1) * soPhanTuMotHang;
			gotoxy(5 + i * 9, 11 + (soHang)*2);
			if (p.danhsachVe[vitri] != "0")
			{
				SetColor(6); // ghe da co nguoi ngoi
				cout << vitri;
				continue;
			}
			SetColor(7); // ghe chua co nguoi ngoi
			cout << vitri;
		}
	}
	SetColor(7); // xet lai mau chu 
	SetBGColor(0); // xet lai background
}
void ThongKeChuyenBay(List_MayBay &list_MB)
{

	int current_page = 1;
	int total_MB = list_MB.soluong;
	int total_page = (total_MB % 10 == 0) ? (total_MB / 10) : (total_MB / 10 + 1);

	if (list_MB.soluong == 0)
	{
		Clear_Frame_Main();
		outtextxy(20, 11, "+-------------------------------------------------------------+");
		outtextxy(20, 11, "|                     DANH SACH TRONG !                       |");
		outtextxy(20, 11, "+-------------------------------------------------------------+");
		system("pause");
		return;
	}
	int vitri_dstk[list_MB.soluong]; // ds dai dien vi tri da sap xep
	for (int i = 0; i < list_MB.soluong; i++)
	{
		vitri_dstk[i] = i;
	}
	if (list_MB.soluong == 1)
	{
		ThongKeTheoTrang(1, 1, list_MB, vitri_dstk);
		return;
	}
	SapXepDanhSachMayBayQuickSort(list_MB, vitri_dstk, 0, list_MB.soluong - 1);
	ThongKeTheoTrang(current_page, total_page, list_MB, vitri_dstk); // trang dau tien
	char key = 0;
	int run = 1;
	while (run)
	{
		key = getch();
		switch (key)
		{
		case PAGEUP:
		{
			// trang truoc
			if (current_page > 1)
			{
				current_page--;
				ThongKeTheoTrang(current_page, total_page, list_MB, vitri_dstk);
			}
			continue;
		}
		case PAGEDOWN:
		{
			// trang ke
			if (current_page < total_page)
			{
				current_page++;
				ThongKeTheoTrang(current_page, total_page, list_MB, vitri_dstk);
			}
			continue;
		}
		case ESC:
		{
			run = 0;
		}
		}
	}
}

void ThongKeTheoTrang(int current_page, int total_page, List_MayBay &list_MB, int *vitri_dstk)
{ 
	Clear_Frame_Main();
	outtextxy(12,7 ,"+-----------------------------------------------------------------------------+");
	outtextxy(12,8 ,"|                             THONG KE LUOT BAY                               |");
	outtextxy(12,9 ,"+-----------------------------------------------------------------------------+");

	outtextxy(12,11,"+--------+-------------------------------------------------+------------------+");
	outtextxy(12,12,"|  STT   |              SO HIEU MAY BAY                    |    SO LUOT BAY   |");
	outtextxy(12,13,"+--------+-------------------------------------------------+------------------+");

	if (current_page < total_page)
	{
		for (int i = 0; i < 20; i = i + 2)
		{
			outtextxy(12,15+i-1,"                                                                              +");
			gotoxy(16, 15 + i - 1);
			cout << i / 2 + 1 + (current_page - 1) * 10;
			outtextxy(12,15+i,"+--------+-------------------------------------------------+------------------+");
		}
		gotoxy(45, 33);
		cout << current_page << "/" << total_page;
	}
	else if (current_page = total_page)
	{
		for (int i = 0; i < (list_MB.soluong % 10) * 2; i = i + 2)
		{	
			outtextxy(12,15+i-1,"                                                                              +");
			gotoxy(16, 15 + i - 1);
			cout << i / 2 + 1 + (total_page - 1) * 10;
			outtextxy(12,15+i,"+--------+-------------------------------------------------+------------------+");
		}
		gotoxy(45, 13 + (list_MB.soluong % 10) * 2);
		cout << current_page << "/" << total_page;
	}

	int number_of_element_this_page; 
	if (current_page == total_page)
	{
		number_of_element_this_page = list_MB.soluong % 10;
	}
	else
	{
		number_of_element_this_page = 10;
	}

	for (int i = 0; i < number_of_element_this_page; i++)
	{
		gotoxy(42, 14 + i * 2);
		cout << list_MB.nodes[vitri_dstk[i + (current_page - 1) * 10]]->sohieu_maybay;
		gotoxy(80, 14 + i * 2);
		cout << list_MB.nodes[vitri_dstk[i + (current_page - 1) * 10]]->sochuyendabay;
	}
}

// quick sort
void SapXepDanhSachMayBayQuickSort(List_MayBay &list_MB, int vitri_dstk[], int q, int r)
{ 
	int temp;
	int i = q;
	int j = r;
	int x = list_MB.nodes[vitri_dstk[(q + r) / 2]]->sochuyendabay;
	do
	{
		while (list_MB.nodes[vitri_dstk[i]]->sochuyendabay > x)
			i++;
		while (list_MB.nodes[vitri_dstk[j]]->sochuyendabay < x)
			j--;
		if (i <= j)
		{
			swapInt(vitri_dstk[i], vitri_dstk[j]);
			i++;
			j--;
		}

	} while (i < j);

	if (q < j)
		SapXepDanhSachMayBayQuickSort(list_MB, vitri_dstk, q, j);
	if (i < r)
		SapXepDanhSachMayBayQuickSort(list_MB, vitri_dstk, i, r);
}
