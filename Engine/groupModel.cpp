//
// Created by José Santos on 29/03/2020.
//

#include "groupModel.h"

GroupModel newGroupModel() {
    GroupModel r = (GroupModel)(malloc(sizeof(struct _groupModel)));
    r->scale = nullptr;
    r->groups = new std::vector<GroupModel>();
    r->models = new std::vector<model>();
    r->rotation = nullptr;
    r->translation = nullptr;
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


void addModel(GroupModel groupModel,model model) {
    if(groupModel) {
        groupModel->models->push_back(model);
    }

}

void addGroup(GroupModel groupModel,GroupModel group2) {
    if(groupModel) {
        groupModel->groups->push_back(group2);
    }
}

std::vector<_groupModel*> getGroups(GroupModel groupModel) {

    if (groupModel) {
    
        std::vector<GroupModel> tmp = *groupModel->groups->front()->groups;
        return tmp;
    }
    std::vector<_groupModel*> a;
    return a;

}

void drawGroupModel(std::vector<GroupModel>::iterator it,int objectCount,int time) {

 
    for (int i = 0; i < objectCount; i++) {
        glPushMatrix();
        float tmpx = translationGetX((*it)->translation);
        float tmpy = translationGetY((*it)->translation);
        float tmpz = translationGetZ((*it)->translation);

        float stmpx = scaleGetX((*it)->scale);
        float stmpy = scaleGetY((*it)->scale);
        float stmpz = scaleGetZ((*it)->scale);

        float a = rotationGetX((*it)->rotation);
        float b = rotationGetY((*it)->rotation);
        float c = rotationGetZ((*it)->rotation);
        float d = rotationGetAngle((*it)->rotation);
         
        float res = 360*(time / d);


        glRotatef(time,0,1,0);
        glTranslatef(tmpx, tmpy, tmpz);
        glScalef(stmpx, stmpy, stmpz);
        drawModel((*it)->models->front());
        glPopMatrix();
        it++;

    }

    for (int j = objectCount; j > 0; j--) {
        it--;

    }



}


