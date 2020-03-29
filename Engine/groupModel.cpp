//
// Created by José Santos on 29/03/2020.
//

#include "groupModel.h"

GroupModel newGroupModel() {
    GroupModel r = (GroupModel)(malloc(sizeof(_groupModel)));
    return r;
}


void setRotation(GroupModel groupModel, Rotation r) {
    if(groupModel)
    groupModel->rotation = r;
}


void setTranslation(GroupModel groupModel, Translation r) {
    if(groupModel)
        groupModel->translation = r;
}


void setScale(GroupModel groupModel, Scale r) {
    if(groupModel)
        groupModel->scale = r;
}

void setGroup(GroupModel groupModel, std::vector<GroupModel> vector) {
    if(groupModel)
        groupModel->groups = std::vector<GroupModel>(vector);
}

void setModels(GroupModel groupModel, std::vector<model> modelvector) {
    if (groupModel)
        groupModel->models = std::vector<model>(modelvector);
}

void addModel(GroupModel groupModel,model model) {
    if(groupModel)
        groupModel->models.push_back(model);
}

void addGroup(GroupModel groupModel,GroupModel group2) {
    if(groupModel)
        groupModel->groups.push_back(group2);
}


std::vector<_groupModel*> getGroups(GroupModel groupModel) {
    if(groupModel)
    return groupModel->groups;
}

std::vector<model> getModels(GroupModel groupModel) {
    if(groupModel)
        return groupModel->models;
}