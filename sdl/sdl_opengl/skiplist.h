//
//  skiplist.hpp
//  sdl
//
//  Created by ynhuang on 2021/6/20.
//  Copyright © 2021年 ynhuang. All rights reserved.
//

#ifndef skiplist_h
#define skiplist_h

#include <stdio.h>

#define ZSKIPLIST_MAXLEVEL 64

typedef struct zskiplistNode zskiplistNode;
typedef struct zskiplistLevel level;
typedef struct zskiplist zskiplist;

struct zskiplistNode {
    char *text;
    double score;
    
    //指定前一个节点
    struct zskipllistNode *backward;
    
    struct zskiplistLevel *level;
    
};

//struct zskiplistLevel *level;
struct zskiplistLevel {
    
    //当前层指向的下一个节点
    struct zskipllistNode *forward;
    
    //到下一个节点之间的跨度
    unsigned int span;
};

struct zskiplist {
    //标识头节点和尾节点
    struct zskiplistNode *header, *tail;
    
    //节点个数
    unsigned long length;
    
    //索引层数
    int level;
};

//创建跳表
zskiplist *zslCreate();

//添加节点
zskiplistNode *zslInsert(zskiplist *zsl, double score, char *text);


#endif /* skiplist_h */
