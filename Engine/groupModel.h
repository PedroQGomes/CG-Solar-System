//
// Created by José Santos on 29/03/2020.
//

#ifndef CG_19_20_GROUPMODEL_H
#define CG_19_20_GROUPMODEL_H

#include "rotation.h"
#include "translation.h"
#include "scale.h"
#include "model.h"
#include <GL/glut.h>


struct _groupModel {
    Rotation rotation;
    Translation translation;
    Scale scale;
    std::vector<Model> *models;
    std::vector<_groupModel*> *groups;
};

typedef struct _groupModel* GroupModel;



GroupModel newGroupModel();
void setRotation(GroupModel groupModel, Rotation r);
void setTranslation(GroupModel groupModel, Translation r);
void setScale(GroupModel groupModel, Scale r);
void setGroup(GroupModel groupModel, std::vector<GroupModel> vector);
void setModels(GroupModel groupModel, std::vector<Model> modelvector);
std::vector<_groupModel*> getGroups(GroupModel groupModel);
void addModel(GroupModel groupModel,Model model);
void addGroup(GroupModel groupModel,GroupModel group2);
void drawGroupModel(std::vector<GroupModel>::iterator it,int objectCount,int time);
void fillALLbuff(std::vector<GroupModel>::iterator it, int objectCount);
void textureALLModels(std::vector<GroupModel>::iterator it, int objectCount);

#endif //CG_19_20_GROUPMODEL_H
