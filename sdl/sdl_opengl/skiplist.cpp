//
//  skiplist.cpp
//  sdl
//
//  Created by ynhuang on 2021/6/20.
//  Copyright © 2021年 ynhuang. All rights reserved.
//

#include "skiplist.h"
#include <stdlib.h>

zskiplistNode *zslCreateNode(int level, double score, char* text) {
    
    //node 分配内存
    zskiplistNode *zn = (zskiplistNode*)malloc(sizeof(*zn) + level * sizeof(struct zskiplistLevel));
    
    //填充数据
    zn->score = score;
    zn->text = text;
    return zn;
    
}

zskiplist *zslCreate() {
    
    int j;
    zskiplist *zsl;
    
    //分配内存
    zsl = (zskiplist*)malloc(sizeof(*zsl));
    
    zsl->level = 1;
    zsl->length = 0;
    zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL,0,NULL);
    
    for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++) {
        //头结点每个level的下一个节点都初始化为null，跨度为0
        zsl->header->level[j].forward = NULL;
        zsl->header->level[j].span = 0;
    }
    
    zsl->header->backward = NULL;
    zsl->tail = NULL;
    
    return zsl;
    
}

zskiplistNode *zslInsert(zskiplist *zsl, double score, char *text) {
    
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    
    unsigned int rank[ZSKIPLIST_MAXLEVEL];
    
    int i, level;
    
    x = zsl->header;
    //从最高层到底层去查找位置
    for (i = zsl->level - 1; i >= 0; i--) {
        rank[i] = (i == (zsl->level - 1) ? 0 : rank[i+1]);
        
        while (x->level[i].forward && ((zskiplistNode *)x->level[i].forward)->score < score) {
            rank[i] += x->level[i].span;
            x = (zskiplistNode *)x->level[i].forward;
        }
        
        update[i] = x;
    }
    
    //算法随机生成当前层数，那就需要变更上个节点的span
    
    return nullptr;
}
