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
     
        float stmpx = scaleGetX((*it)->scale);
        float stmpy = scaleGetY((*it)->scale);
        float stmpz = scaleGetZ((*it)->scale);

        
        drawTranslation((*it)->translation, time);
        //glRotatef(time,0,1,0);
        //glTranslatef(tmpx, tmpy, tmpz);
        drawRotation((*it)->rotation,time);
        glScalef(stmpx, stmpy, stmpz);
        drawModel(&((*it)->models->front()));

        for (int j = 0; j < (*it)->groups->size(); j++) {
            drawTranslation((*it)->groups->at(j)->translation, time);
            float stmpx = scaleGetX((*it)->groups->at(j)->scale);
            float stmpy = scaleGetY((*it)->groups->at(j)->scale);
            float stmpz = scaleGetZ((*it)->groups->at(j)->scale);
            glScalef(stmpx, stmpy, stmpz);

            drawModel(&(*it)->groups->at(j)->models->front());

        }

        glPopMatrix();
        it++;

    }

    for (int j = objectCount; j > 0; j--) {
        it--;

    }

}

void fillALLbuff(std::vector<GroupModel>::iterator it, int objectCount) {
    for (int i = 0; i < objectCount; i++) {
        glColor3b(0.0f, 0.0f, 0.0f);
        fillBuffers(&(*it)->models->front());

       
        for(int j = 0; j < (*it)->groups->size();j++){
        
            fillBuffers(&(*it)->groups->at(j)->models->front());

        }


        it++;

    }
    for (int j = objectCount; j > 0; j--) {
        it--;
         
    }

}


