#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <wx/list.h>

#include "settings.h"
#include "cbeditor.h"

enum EditorInterfaceType
{
	eitTabbed = 0,
	eitMDI
};

WX_DECLARE_LIST(cbEditor, EditorsList);

// forward decls
class wxMenuBar;
class wxNotebook;
class EditorColorSet;
class cbProject;

struct cbFindReplaceData
{
	int start;
	int end;
	wxString findText;
	wxString replaceText;
	bool findInFiles;
	bool matchWord;
	bool startWord;
	bool matchCase;
	bool regEx;
	bool directionDown;
	bool originEntireScope;
	bool scopeSelectedText;
};

/*
 * No description
 */
class DLLIMPORT EditorManager : public wxEvtHandler
{
	public:
        friend class Manager; // give Manager access to our private members
		void CreateMenu(wxMenuBar* menuBar);
		void ReleaseMenu(wxMenuBar* menuBar);
		void Configure();        
		int GetEditorsCount(){ return m_EditorsList.GetCount(); }
		cbEditor* GetEditor(int index);
        cbEditor* GetEditor(const wxString& filename){ return IsOpen(filename); } // synonym of IsOpen()
        cbEditor* IsOpen(const wxString& filename);
        cbEditor* Open(const wxString& filename, int pos = 0);
        cbEditor* GetActiveEditor();
        void SetActiveEditor(cbEditor* ed);
		EditorColorSet* GetColorSet(){ return m_Theme; }
		void SetColorSet(EditorColorSet* theme);
		const EditorInterfaceType& GetEditorInterfaceType(){ return m_IntfType; }
		void SetEditorInterfaceType(const EditorInterfaceType& _type);
        cbEditor* New();
		bool UpdateProjectFiles(cbProject* project);
        bool SwapActiveHeaderSource();
        bool CloseActive();
        bool Close(const wxString& filename);
		bool Close(cbEditor* editor);
        bool Close(int index);
        bool CloseAll();
        bool CloseAllExcept(cbEditor* editor);
        bool Save(const wxString& filename);
        bool Save(int index);
        bool SaveActive();
        bool SaveAs(int index);
        bool SaveActiveAs();
        bool SaveAll();
		int ShowFindDialog(bool replace);
		int Find(cbEditor* editor, cbFindReplaceData* data);
		int Replace(cbEditor* editor, cbFindReplaceData* data);
		int FindNext(bool goingDown);
    private:
        static EditorManager* Get(wxWindow* parent);
		static void Free();
		EditorManager(wxWindow* parent);
		~EditorManager();
        void UpdateEditorIndices();
		void CalculateFindReplaceStartEnd(cbEditor* editor, cbFindReplaceData* data);
        EditorsList m_EditorsList;
		cbFindReplaceData* m_LastFindReplaceData;
		EditorColorSet* m_Theme;
		EditorInterfaceType m_IntfType;
};

#endif // EDITORMANAGER_H

