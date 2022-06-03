//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
#include <windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
sqlite3* Database;
int id;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1 -> NodeDataSize = sizeof(TreeNodeStruct);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	VirtualStringTree1 -> Clear();
    sqlite3_stmt *pStatement;
	int result = sqlite3_prepare16_v2(Database, L"DELETE FROM moz_origins; VACUUM;", -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		Application->MessageBox(L"Ошибка при выполнении запроса БД!",L"ERROR", MB_OK);
		return;
	}

    result = sqlite3_step(pStatement);
	if(result != SQLITE_DONE)
	{
		Application->MessageBox(L"Ошибка при очистке БД!",L"ERROR", MB_OK);
        return;
	}
	sqlite3_finalize(pStatement);
}


//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    sqlite3_close(Database);
	Form1 -> Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	sqlite3_stmt *pStatement;
	int result = sqlite3_prepare16_v2(Database, L"SELECT * FROM moz_origins ORDER BY id;", -1, &pStatement, NULL);
	while (true) {

		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE) break;
		else if (result == SQLITE_ROW) {
			PVirtualNode entryNode = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(entryNode);
			nodeData -> id = sqlite3_column_int(pStatement,0);
			nodeData -> prefix = (UnicodeString)(char*)sqlite3_column_text(pStatement,1);
			nodeData -> host = (UnicodeString)(char*)sqlite3_column_text(pStatement,2);
			nodeData -> frecency = sqlite3_column_int(pStatement,3);
			 }
		else {
			Application->MessageBox(L"Ошибка при загрузке БД!",L"ERROR", MB_OK);
			break;
		}

	}
	sqlite3_finalize(pStatement);
	VirtualStringTree1 -> EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
		if (!Node) return;
		TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(Node);

		switch (Column) {

			case 0:
			{
				CellText = UnicodeString(nodeData -> id);  break;
			}
			case 1:
			{
				CellText = nodeData -> prefix; break;
			}
			case 2:
			{
				CellText = nodeData -> host; break;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
		  PVirtualNode Node)
{
	if (!Node) return;
    Button5 -> Enabled = True;
	TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(Node);
    id = nodeData -> id;
	Label2 -> Caption = UnicodeString(nodeData -> frecency);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int OpenResult = sqlite3_open16(L".\\places.sqlite", &Database);
	Application->MessageBox(L"База данных загружена",L"Message", MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	sqlite3_stmt *pStatement;
	std::wstring delrow = L"DELETE FROM moz_origins WHERE id = " + std::to_wstring(id) + L";";
	const wchar_t* sql = delrow.c_str();
	int result = sqlite3_prepare16_v2(Database, sql, -1, &pStatement, NULL);
	if(result != SQLITE_OK)
	{
		Application->MessageBox(L"Ошибка при удалении записи БД!",L"ERROR", MB_OK);
		return;
	}
	result = sqlite3_step(pStatement);

	if(result != SQLITE_DONE)
	{
		Application->MessageBox(L"Ошибка при удалении записи БД!",L"ERROR", MB_OK);
		return;
	}
	sqlite3_finalize(pStatement);

	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	result = sqlite3_prepare16_v2(Database, L"SELECT * FROM moz_origins ORDER BY id;", -1, &pStatement, NULL);
	 while (true) {

		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE) break;
		else if (result == SQLITE_ROW) {
			PVirtualNode entryNode = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(entryNode);
			nodeData -> id = sqlite3_column_int(pStatement,0);
			nodeData -> prefix = (UnicodeString)(char*)sqlite3_column_text(pStatement,1);
			nodeData -> host = (UnicodeString)(char*)sqlite3_column_text(pStatement,2);
			nodeData -> frecency = sqlite3_column_int(pStatement,3);
			 }
		else {
			Application->MessageBox(L"Ошибка при загрузке БД!",L"ERROR", MB_OK);
			break;
		}

	}
	sqlite3_finalize(pStatement);
	VirtualStringTree1 -> EndUpdate();
}

//---------------------------------------------------------------------------

