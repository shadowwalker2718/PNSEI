//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_FIND_DUPLICATE_FILES_H
#define PNSEI_FIND_DUPLICATE_FILES_H

/* https://www.1point3acres.com/bbs/thread-361979-1-1.html

今天刚刚面完Dropbox onsite。分享一下phone screen和onsite的面经，求人品，求offer。

感谢地里其他面经，6轮面试中有5轮都是面经题。 来源一亩.三分地论坛.

两轮电面:

1.  find duplicate files. 没有明确给requirement，也没有给函数让实现。只能和面试官讨论确认requirement细节。讨论过程中提到了文件很大的问题。给出了先用size分类，再比较sample hash，最后比较full hash的solution。确认可行以后开始实现，定义了一个MetaData类来记录文件的size, sample hash, full hash的信息，然后override了hashCode和equals方法。Sample hash和full hash用了lazy initialization。这样每次读取一个文件，就可以生成一个文件的MetaData，把这个MetaData放到Set里就可以查询是否存在过duplicate file。.
MetaData类的定义大概是这样:
//MetaData类的定义大概是这样:

class MetaData {
    String path;
    int size;
    String sampleHash;
    String fullHash;

    public MetaData(String path) {
        //read file and get size, init size
    }

    public String getSampleHash() {
        if (sampleHash == null) {
             // read file and do sampling, apply MD5 or SHA on the samples
             // assign to sampleHash
        }
        return sampleHash;
    }

    public String getFullHash() {
        // similar to sampleHash
    }

    @override
    public int hashCode() {
        return size;
    }

    @override
    public boolean equals(Object that) {
        if (!that.getClass().isAssignble(this.getClass)) {
            return false;
        }

        if (this.getSampleHash() != that.getSampleHash()) {
            return false;
        }

        return this.getFullHash() == that.getFullHash();
    }
}

https://automationrhapsody.com/md5-sha-1-sha-256-sha-512-speed-performance/
*/

// https://stackoverflow.com/questions/8236/how-do-you-determine-the-size-of-a-file-in-c



#endif //PNSEI_FIND_DUPLICATE_FILES_H
