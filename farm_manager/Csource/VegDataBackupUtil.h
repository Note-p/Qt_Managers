//
// Created by hunto on 2017/9/6 0006.
//

#ifndef CSOURCE_VEGDATABACKUPUTIL_H
#define CSOURCE_VEGDATABACKUPUTIL_H

/*
 * @usage:  将数据文件备份至指定路径
 * @return: 1--保存成功  0--保存失败
 */
int backupDataFileTo (char *filePath);

/*
 * @usage:  从指定路径读取备份文件还原至数据库
 * @return: 1--读取成功  0--读取失败
 */
int getDataFileFromBackupFile (char *filePath);

#endif //CSOURCE_VEGDATABACKUPUTIL_H
