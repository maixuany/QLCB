#pragma once
#include <iostream>
#include <string>
#include "date.h"
#include "sub_function.h"
#include "mylib.h"
using namespace std;

const int MAXLIST_MAYBAY = 300;
const int MAX_LENGTH_SHMB = 15;
const int MAX_LENGTH_LOAIMB = 40;
const int MAX_LENGTH_MACB = 15;
const int MAX_LENGTH_CMND = 12;
const int MAX_LENGTH_HO = 30;
const int MAX_LENGTH_TEN = 20;

using namespace std;

//======================= MAY BAY =======================
struct MayBay
{
    char sohieu_maybay[MAX_LENGTH_SHMB+1]; 
    char loai_maybay[MAX_LENGTH_LOAIMB+1];
    int socho;
    int sochuyendabay = 0;
};

struct List_MayBay
{
    int soluong = 0;
    MayBay *nodes[MAXLIST_MAYBAY];
};

MayBay* Init_MB(MayBay mb){
    MayBay* temp = new MayBay;
    *temp = mb;
    return temp;
}

bool listMBEmpty(List_MayBay list){
    return list.soluong==0;
}

bool listMBFull(List_MayBay list){
    return list.soluong>=MAXLIST_MAYBAY;
}

void Add_MB_to_List(List_MayBay &list,MayBay mb){
    if(listMBFull(list)) return;
    list.nodes[list.soluong] = Init_MB(mb);
    list.soluong++;
}
int timkiem_MB(List_MayBay l, char* sohieuMB){
	for(int i=0;i<l.soluong;i++)
		if(strcmp(l.nodes[i]->sohieu_maybay, sohieuMB)==0)	return i;
	return -1;
}

void xoa_mb_khoids(List_MayBay &dsmb , int vitri){
	delete dsmb.nodes[vitri];
	for(int i=vitri; i< dsmb.soluong -1; i++ )
		dsmb.nodes[i]= dsmb.nodes[i+1];
	dsmb.soluong--;
}
void edit_mb(List_MayBay &dsmb , int vitri, MayBay &mb){
	    *dsmb.nodes[vitri]=  mb ;
}
//==================== MAY BAY =================== }

struct ChuyenBay
{
    char ma_chuyenbay[MAX_LENGTH_MACB+1]; 
    Day_time ngaykhoihanh; 
    string sanbayden;
    int trangthai; 
    char sohieu_maybay[MAX_LENGTH_SHMB+1]; 
    string *danhsachVe;
    int soVe;
};

struct NodeChuyenBay
{
    ChuyenBay data;
    NodeChuyenBay *next;
};

typedef struct NodeChuyenBay* PTR_ChuyenBay;

struct HanhKhach
{
    char CMND[MAX_LENGTH_CMND+1];
    char ho[MAX_LENGTH_HO+1];
    char ten[MAX_LENGTH_TEN+1];
    int phai; //1: Male, 0: Female
};

struct NodeHanhKhach
{
    HanhKhach info;
    struct NodeHanhKhach *left, *right;
};

typedef NodeHanhKhach* PTR_HK;



void Init_CB(List_MayBay &l, ChuyenBay &a){
	a.trangthai = CONVE;
	a.soVe = l.nodes[timkiem_MB(l, a.sohieu_maybay)]->socho;
	a.danhsachVe = new string[a.soVe+1];
	for(int i=1;i<=a.soVe;i++){
		a.danhsachVe[i] = "0";
	}
}

PTR_ChuyenBay Init_Node_CB(ChuyenBay cb){
    NodeChuyenBay* temp = new NodeChuyenBay;
    temp->data = cb;
    temp->next = NULL;
    return temp;
}
bool listCBEmpty(PTR_ChuyenBay list){
	return list==NULL;
}
PTR_HK Init_HK(HanhKhach hk){
    NodeHanhKhach *temp = new NodeHanhKhach;
    temp->info = hk;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}


void Add_HK_to_List(PTR_HK &root, HanhKhach &hk){
    if(root == NULL){
        PTR_HK temp = Init_HK(hk);
        root = temp;
    }
    else{
        if(ChangeCharToNum(hk.CMND)<ChangeCharToNum(root->info.CMND)) Add_HK_to_List(root->left, hk);
        else if(ChangeCharToNum(hk.CMND)>ChangeCharToNum(root->info.CMND)) Add_HK_to_List(root->right, hk);
    }
}

void Add_CB_to_List(PTR_ChuyenBay &First, ChuyenBay cb){
    PTR_ChuyenBay nodeNew = Init_Node_CB(cb);
    if(First==NULL){
        First = nodeNew;
        First->next = NULL;
    }else{
        PTR_ChuyenBay nodeChay = First;
        for(nodeChay = First; nodeChay->next!=NULL; nodeChay=nodeChay->next);
        nodeChay->next = nodeNew;
    }
}



int checkFull_CB(PTR_ChuyenBay First){
	for(int i=1;i<=First->data.soVe;i++){
		if(First->data.danhsachVe[i]=="0") return 0;
	}
	First->data.trangthai = HETVE;
	return 1;
}

void checkHoanTat(PTR_ChuyenBay &p, List_MayBay &dsmb){
	if(p->data.trangthai==CONVE||p->data.trangthai==HETVE){
		if(TGQK(p->data.ngaykhoihanh)==true){
			p->data.trangthai = HOANTAT;
			dsmb.nodes[timkiem_MB(dsmb, p->data.sohieu_maybay)]->sochuyendabay++;
		}
	}
}

void check_HoanTat_All(PTR_ChuyenBay &First, List_MayBay &list){
	PTR_ChuyenBay a;
	for(a = First; a!=NULL;a=a->next){
		checkHoanTat(a, list);
	}
}

int sovechuaban(ChuyenBay a){
	int count = 0;
	for(int i=1;i<=a.soVe;i++)
		if(a.danhsachVe[i]=="0") count++;
	return count;
}

PTR_HK timkiem_HK(PTR_HK root, char* CMND){
	PTR_HK nodeRun = root;
	while(nodeRun!=NULL&&ChangeCharToNum(CMND)!=ChangeCharToNum(nodeRun->info.CMND)){
		if(ChangeCharToNum(CMND)>ChangeCharToNum(nodeRun->info.CMND)) nodeRun = nodeRun->right;
		else nodeRun=nodeRun->left;
	}
	return nodeRun;
}
