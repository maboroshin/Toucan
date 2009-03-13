/////////////////////////////////////////////////////////////////////////////////
// Author:      Steven Lamerton
// Copyright:   Copyright (C) 2009 Steven Lamerton
// License:     GNU GPL 2 (See readme for more info)
/////////////////////////////////////////////////////////////////////////////////

#include "syncbase.h"
#include "syncpreview.h"
#include "../md5.h"
#include <list>
#include <map>
#include <wx/string.h>

SyncPreview::SyncPreview(wxString syncsource, wxString syncdest, SyncData* syncdata, Rules syncrules, bool issource){
	this->sourceroot = syncsource;
	this->destroot = syncdest;
	this->data = syncdata;
	this->rules = syncrules;
	this->sourcetree = issource;
}

VdtcTreeItemBaseArray SyncPreview::Execute(){
	std::list<wxString> sourcepaths = FolderContentsToList(sourceroot);
	std::list<wxString> destpaths = FolderContentsToList(destroot);
	std::map<wxString, short> mergeresult = MergeListsToMap(sourcepaths, destpaths);
	OperationCaller(mergeresult);
	return items;
}

bool SyncPreview::OperationCaller(std::map<wxString, short> paths){
	for(std::map<wxString, short>::iterator iter = paths.begin(); iter != paths.end(); ++iter){
		if(wxDirExists(sourceroot + wxFILE_SEP_PATH + (*iter).first) || wxDirExists(destroot + wxFILE_SEP_PATH + (*iter).first)){
			if((*iter).second == 1){
				OnSourceNotDestFolder((*iter).first);
			}
			else if((*iter).second == 2){
				OnNotSourceDestFolder((*iter).first);				
			}
			else if((*iter).second == 3){
				OnSourceAndDestFolder((*iter).first);
			}
		}
		//We have a file
		else{
			if((*iter).second == 1){
				OnSourceNotDestFile((*iter).first);
			}
			else if((*iter).second == 2){
				OnNotSourceDestFile((*iter).first);				
			}
			else if((*iter).second == 3){
				OnSourceAndDestFile((*iter).first);
			}
		}
	}
	return true;
}

bool SyncPreview::OnSourceNotDestFile(wxString path){
	
	return true;
}
bool SyncPreview::OnNotSourceDestFile(wxString path){

	return true;
}
bool SyncPreview::OnSourceAndDestFile(wxString path){

	return true;
}
bool SyncPreview::OnSourceNotDestFolder(wxString path){
	//Simply reutrn as the virtualdirtreectrl does the folder handling
	return true;
}
bool SyncPreview::OnNotSourceDestFolder(wxString path){
	//Simply reutrn as the virtualdirtreectrl does the folder handling
	return true;
}
bool SyncPreview::OnSourceAndDestFolder(wxString path){
	//Simply reutrn as the virtualdirtreectrl does the folder handling
	return true;
}