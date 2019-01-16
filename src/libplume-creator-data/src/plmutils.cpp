/***************************************************************************
*   Copyright (C) 2018 by Cyril Jacquet                                 *
*   cyril.jacquet@plume-creator.eu                                        *
*                                                                         *
*  Filename: plmutils.cpp                                                   *
*  This file is part of Plume Creator.                                    *
*                                                                         *
*  Plume Creator is free software: you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by   *
*  the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                    *
*                                                                         *
*  Plume Creator is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with Plume Creator.  If not, see <http://www.gnu.org/licenses/>. *
***************************************************************************/
#include "plmutils.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QSettings>
#include  <QtCore>

// #include "zipper/zipchecker.h"


/*!
   Delete a directory along with all of its contents.

   \param dirName Path of directory to remove.
   \return true on success; false on error.
 */
bool PLMUtils::Dir::removeDir(const QString& dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH (QFileInfo info,
                   dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System |
                                     QDir::Hidden  |
                                     QDir::AllDirs | QDir::Files,
                                     QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }

        result = dir.rmdir(dirName);
    }

    return result;
}

// ------------------------------------------------------------------


// int PLMUtils::addProjectToSettingsArray(QString fileName)
// {
//    int arrayNumber;
//    QString projectName, projectDirectory, workingPath, lastModifiedDate,
// creationDate;

//    QFile file(fileName);
//    if(!file.exists())
//        return 999;


//    //  creation date :

//    QString tempFileName = QDir::tempPath() + "/Plume/info";
//    QString infoFileName = JlCompress::extractFile(fileName, "info",
// tempFileName );
//    QFile *infoFile = new QFile(infoFileName);

//    QDomDocument infoDomDoc;
//    QString errorStr;
//    int errorLine,errorColumn;

//    if (!infoDomDoc.setContent(infoFile, true, &errorStr, &errorLine,
//                               &errorColumn)) {
//        qDebug() << QString("Info File. Parse error at line %1, column
// %2:\n%3\n")
//                    .arg(errorLine)
//                    .arg(errorColumn)
//                    .arg(errorStr);


//        return 999;
//    }

//    QDomElement infoRoot = infoDomDoc.documentElement();
//    if (infoRoot.tagName() != "plume-information") {
//        qDebug() << "The file is not a Plume Creator info file.";
//        return 999;
//    }
//    creationDate =
// infoRoot.firstChildElement("prj").attribute("creationDate");

//    infoFile->close();

//    infoFile->remove();


//    // path :
//    projectDirectory = file.fileName();
//    projectDirectory.chop(file.fileName().split("/").last().size());


//    //name :
//    projectName = file.fileName().split("/").last().remove(".plume");


//    QSettings settings;


//    settings.beginGroup("Manager/projects");

//    QStringList groups = settings.childGroups();
//    int size = groups.size();
//    settings.setValue("size", size);


//    settings.endGroup();


//    size = settings.value("Manager/projects/size", 0).toInt();


//    settings.beginWriteArray("Manager/projects");
//    settings.setArrayIndex(size);
//    settings.setValue("name", projectName);
//    settings.setValue("path", projectDirectory);
//    settings.setValue("workPath", "OBSOLETE");
//    settings.setValue("lastModified",
// QDateTime::currentDateTime().toString(Qt::ISODate));
//    settings.setValue("creationDate", creationDate);

//    settings.endArray();


//    arrayNumber = size;

//    return arrayNumber;
// }

bool PLMUtils::ProjectsArrayInSettings::modifyProjectModifiedDateInSettingsArray(
    int     arrayNumber,
    QString date)
{
    QSettings settings;

    settings.beginWriteArray("Manager/projects");
    settings.setArrayIndex(arrayNumber);
    settings.setValue("lastModified", date);
    settings.endArray();
    return true;
}

int PLMUtils::ProjectsArrayInSettings::findProjectInSettingArray(QString fileName)
{
    QFile file(fileName);

    if (!file.exists()) {
        return 999;
    }

    if (!PLMUtils::ProjectsArrayInSettings::isProjectExistingInSettingArray(
            fileName)) {
        return 999;
    }

    QSettings settings;
    settings.beginGroup("Manager/projects");
    QStringList groups = settings.childGroups();
    int size           = groups.size();
    settings.setValue("size", size);
    settings.endGroup();
    QString name, path, workPath;
    settings.beginReadArray("Manager/projects");

    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        name     = settings.value("name").toString();
        path     = settings.value("path").toString();
        workPath = settings.value("workPath").toString();
        QFile arrayFile;

        if (workPath == "OBSOLETE") { // new version
            arrayFile.setFileName(path + "/" +  name + ".plume");

            if (file.fileName() == arrayFile.fileName()) {
                return i;
            }
        } else { // old system
            arrayFile.setFileName(workPath + "/" +  name + ".plume");

            if (file.fileName() == arrayFile.fileName()) {
                return i;
            }
        }
    }

    settings.endArray();
    return 999;
}

bool PLMUtils::ProjectsArrayInSettings::isProjectExistingInSettingArray(
    QString fileName)
{
    QFile file(fileName);
    QSettings settings;

    settings.beginGroup("Manager/projects");
    QStringList groups = settings.childGroups();
    int size           = groups.size();
    settings.setValue("size", size);
    settings.endGroup();
    QString name, path, workPath;
    settings.beginReadArray("Manager/projects");

    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        name     = settings.value("name").toString();
        path     = settings.value("path").toString();
        workPath = settings.value("workPath").toString();
        QFile arrayFile;

        if (workPath == "OBSOLETE") { // new version
            arrayFile.setFileName(path + "/" + name + ".plume");

            //            qDebug() << arrayFile.fileName() + "   " +
            // file.fileName();
            if (file.fileName() == arrayFile.fileName()) {
                return true;
            }
        } else { // old system
            arrayFile.setFileName(workPath + "/" +  name + ".plume");

            if (file.fileName() == arrayFile.fileName()) {
                return true;
            }
        }
    }

    settings.endArray();
    return false;
}

// int PLMUtils::adaptSettingArrayToProject(QString fileName)
// {
//    int arrayNumber;
//    if(!PLMUtils::isProjectExistingInSettingArray(fileName)){
//        arrayNumber = PLMUtils::addProjectToSettingsArray(fileName);
//        qDebug() << "project added ";
//    }
//    else
//        arrayNumber = PLMUtils::findProjectInSettingArray(fileName);

//    return arrayNumber;
// }


// void PLMUtils::sortSettingsArray()
// {
//    QMultiMap<int, QString> projName, projPath, projWorkPath,
// projLastModifiedTime, projCreationDate;
//    QMultiMap<int, QString> newProjName, newProjPath, newProjWorkPath,
// newProjLastModifiedTime, newProjCreationDate;


//    QSettings settings;


//    settings.beginReadArray("Manager/projects");

//    for (int i = 0; i < 100; ++i) {
//        settings.setArrayIndex(i);

//        projName.insert(i, settings.value("name").toString());
//        projPath.insert(i, settings.value("path").toString());
//        projWorkPath.insert(i, settings.value("workPath").toString());
//        projLastModifiedTime.insert(i,
// settings.value("lastModified").toString());
//        projCreationDate.insert(i, settings.value("creationDate").toString());


//    }

//    settings.endArray();


//    // keep only the existing projects

//    int b = 0;
//    for (int p = 0; p < projName.size(); ++p) {

//        QString projNameI = projName.value(p);
//        QString projPathI = projPath.value(p);
//        QString projWorkPathI = projWorkPath.value(p);
//        QString projLastModifiedTimeI = projLastModifiedTime.value(p);
//        QString projCreationDateI = projCreationDate.value(p);

//        if(projNameI.isEmpty() && projPathI.isEmpty()){
//            projName.remove(p);
//            projPath.remove(p);
//            projWorkPath.remove(p);
//            projLastModifiedTime.remove(p);
//            projCreationDate.remove(p);


//            continue;


//        }
//        else if( ( QFile(projPathI + "/"+ projNameI + ".plume").exists() ||
//                   QFile(projWorkPathI +"/"+  projNameI + ".plume").exists() )
//                 &&
//                 ( newProjName.keys(projNameI).size() == 0 &&
// newProjCreationDate.keys(projCreationDateI).size() == 0 )
//                 ){ // check if ewist and avoid doubles


//            newProjName.insert(b, projNameI);
//            newProjPath.insert(b, projPathI);
//            newProjWorkPath.insert(b, projWorkPathI);
//            newProjLastModifiedTime.insert(b,projLastModifiedTimeI );
//            newProjCreationDate.insert(b, projCreationDateI);
//            b += 1;
//        }


//    }


//    settings.beginGroup("Manager/projects");

//    int size = newProjName.size();
//    settings.setValue("size", size);

//    settings.endGroup();


//    settings.beginWriteArray("Manager/projects");

//    for (int q = 0; q < newProjName.size(); ++q) {
//        settings.setArrayIndex(q);

//        settings.setValue("name",newProjName.value(q));
//        settings.setValue("path",newProjPath.value(q));
//        settings.setValue("workPath",newProjWorkPath.value(q));
//        settings.setValue("lastModified",newProjLastModifiedTime.value(q));
//        settings.setValue("creationDate",newProjCreationDate.value(q));


//    }

//    settings.endArray();


//    settings.beginGroup("Manager/projects");
//    int grSize = settings.childGroups().size();
//    settings.endGroup();

//    settings.beginWriteArray("Manager/projects");
//    for (int r = newProjName.size(); r < grSize; ++r) {
//        settings.setArrayIndex(r);
//        settings.remove("");
//    }
//    settings.endArray();

// }

// -------------------------------------------------------------

QHash<QString,
      QString>PLMUtils::ProjectsArrayInSettings::listAllProjectsInSettingsArray()
{
    QSettings settings;

    settings.beginGroup("Manager/projects");
    QStringList groups = settings.childGroups();
    int size           = groups.size();
    settings.setValue("size", size);
    settings.endGroup();
    QString name, path;
    QHash<QString, QString> hash;
    settings.beginReadArray("Manager/projects");

    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        name = settings.value("name").toString();
        path = settings.value("path").toString();
        hash.insert(path, name);
    }

    settings.endArray();
    return hash;
}

// -------------------------------------------------------------


// bool PLMUtils::isProjectFromOldSystem(QString file)
// {
//    if(ZipChecker::isZip(file))
//        return false;
//    else
//        return true;// means this version is < 0.3

//    return false;
// }

// QString PLMUtils::updateProjectIfOldSystem(QString file)
// {

//    FileUpdater updater;

//    updater.checkAttendanceFile(file);
//    updater.checkInfoFile(file);
//    updater.checkTreeFile(file);

//    QFileInfo info(file);
//    QDir directory = info.dir();
//    directory.cdUp();
//    JlCompress::compressDir(directory.absolutePath() + "/" + info.fileName(),
// info.absolutePath());

//    file = directory.absolutePath() + "/" + info.fileName();


//    //           update the project manager if project is in the manager :

//    QSettings settings;
//    int size = settings.value("Manager/projects/size").toInt();

//    settings.beginWriteArray("Manager/projects");

//    for (int i = 0; i < size; ++i) {
//        settings.setArrayIndex(i);

//        //            qDebug() << settings.value("name").toString();
//        //            qDebug() << info.fileName().remove(".plume");
//        //                        qDebug() <<
// settings.value("path").toString();
//        //                        qDebug() << directory.absolutePath();

//        if(settings.value("name").toString() ==
// info.fileName().remove(".plume")
//                &&
// QDir::fromNativeSeparators(settings.value("path").toString()) ==
// directory.absolutePath()){

//            settings.setValue("workPath",  "OBSOLETE");
//        }
//    }
//    settings.endArray();

//    directory.setPath(directory.absolutePath());
//    directory.rename(directory.absolutePath() + "/" +
// info.fileName().remove(".plume") +"/",
//                     directory.absolutePath() + "/obsolete_" +
//  info.fileName().remove(".plume")+"/");


//    return file;
// }

// QString PLMUtils::projectRealName(QString fileName)
// {
//    //  creation date :
//    QString realName;
//    QString tempFileName = QDir::tempPath() + "/Plume/info";
//    QString infoFileName = JlCompress::extractFile(fileName, "info",
// tempFileName );
//    QFile *infoFile = new QFile(infoFileName);

//    if(!infoFile->exists())
//        return "ERROR real name";

//    QDomDocument infoDomDoc;
//    QString errorStr;
//    int errorLine,errorColumn;

//    if (!infoDomDoc.setContent(infoFile, true, &errorStr, &errorLine,
//                               &errorColumn)) {
//        qDebug() << QString("Info File. Parse error at line %1, column
// %2:\n%3\n")
//                    .arg(errorLine)
//                    .arg(errorColumn)
//                    .arg(errorStr);


//        return "ERROR real name";
//    }

//    QDomElement infoRoot = infoDomDoc.documentElement();
//    if (infoRoot.tagName() != "plume-information") {
//        qDebug() << "The file is not a Plume Creator info file.";
//        return "ERROR real name";
//    }
//    realName = infoRoot.firstChildElement("prj").attribute("name");

//    infoFile->close();

//    infoFile->remove();

//    delete infoFile;

//    return realName;
// }


// ------------------------------------------------------------

// QString PLMUtils::parseHtmlText(QString htmlText)
// {


//    QTextEdit *textEdit = new QTextEdit;
//    textEdit->setHtml(htmlText);

//    QTextEdit *finalEdit = new QTextEdit;
//    finalEdit->setHtml(htmlText);
//    finalEdit->toPlainText();
//    finalEdit->toHtml();

//    QTextCursor tCursor = textEdit->textCursor();
//    tCursor.movePosition(QTextCursor::End);
//    int textSize = tCursor.position();
//    tCursor.movePosition(QTextCursor::Start);


//    QTextCursor finalCursor = finalEdit->textCursor();
//    finalCursor.movePosition(QTextCursor::Start);

//    if(textSize == 0)
//        return "";

//    while(tCursor.position() != textSize){


//
//
//
//
//
//    finalCursor.charFormat().setFontItalic(tCursor.charFormat().fontItalic());
//        if(tCursor.charFormat().fontWeight() > 50)
//            finalCursor.charFormat().setFontWeight(75);


//        tCursor.movePosition(QTextCursor::NextCharacter);
//        finalCursor.movePosition(QTextCursor::NextCharacter);


//    }

//    return finalEdit->toHtml();


// }

// void PLMUtils::applyAttributeRecursively(QDomElement element, QString
// attribute, QString value)
// {
//    if(element.isNull())
//        return;


//    element.setAttribute(attribute, value);
//    applyAttributeRecursively(element.firstChild().toElement(), attribute,
// value);

//    QDomElement parentElement = element.parentNode().toElement();
//    QDomElement nextElement = element;

//    for(int i = 0 ; i < parentElement.childNodes().size() ; ++i ){
//        nextElement = nextElement.nextSibling().toElement();
//        applyAttributeRecursively(nextElement, attribute, value);

//    }


// }


QModelIndexList PLMUtils::Models::allChildIndexes(QModelIndex index)
{
    // The first number af the final list is the targeted element
    QModelIndexList childList;

    if (!index.isValid()) {
        return childList;
    }

    //    qDebug() << index.data(Qt::DisplayRole).toString();
    QModelIndex firstChild = index.child(0, 0);

    if (!firstChild.isValid()) {
        return childList;
    }

    childList.append(firstChild);
    allChildIndexes(firstChild);
    QModelIndex siblingChild = firstChild.sibling(firstChild.row() + 1, 0);

    while (siblingChild.isValid()) {
        childList.append(siblingChild);
        allChildIndexes(siblingChild);
        siblingChild = siblingChild.sibling(siblingChild.row() + 1, 0);
    }

    return childList;
}

//
//
// ---------------------------------------------------------------------------------------

QModelIndexList PLMUtils::Models::allParentIndexes(QModelIndex index)
{
    QModelIndexList parentList;

    if (!index.isValid()) {
        return parentList;
    }

    QModelIndex parentIndex =  index.parent();

    if (parentIndex.isValid()) {
        parentList.append(parentIndex);
        allParentIndexes(parentIndex);
    }

    return parentList;
}

//
//
// ---------------------------------------------------------------------------------------


QStringList PLMUtils::Dir::addonsPathsList()
{
    QStringList list;
    QDir dir;

    //    dir.setPath(QCoreApplication::applicationDirPath());

    //    if (dir.isReadable()) {
    //        list.append(dir.path());
    //    }

    dir.setPath(QCoreApplication::applicationDirPath());

    if (dir.cd("plugins"))
        if (dir.isReadable()) {
            list.append(dir.path());
        }

    dir.setPath(QCoreApplication::applicationDirPath());
    dir.cdUp();

    if (dir.cd("plugins"))
        if (dir.isReadable()) {
            list.append(dir.path());
        }
    dir.cdUp();

    if (dir.cd("plugins"))
        if (dir.isReadable()) {
            list.append(dir.path());

            QStringList dirList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
            foreach(const QString &pluginDir, dirList) {
                list.append(dir.path() + "/" + pluginDir);
            }
        }

    dir.setPath(":/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

#ifdef Q_OS_LINUX
    dir.setPath("/usr/share/plume-creator/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

    dir.setPath("/usr/lib/plume-creator/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

    dir.setPath(QDir::homePath() + "/.plume-creator/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

#endif // ifdef Q_OS_LINUX
#ifdef Q_OS_WIN32
    dir.setPath(QCoreApplication::applicationDirPath() + "/share/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

    dir.setPath(
        QDir::homePath() + "/AppData/Roaming/" +
        QCoreApplication::organizationName() + "/share/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

#endif // ifdef Q_OS_WIN32
#ifdef Q_OS_MAC
    dir.setPath("/Library/Application Support/plume-creator/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

    dir.setPath(QDir::homePath() + "/Library/Application Support/plume-creator/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

    dir.setPath(QCoreApplication::applicationDirPath());
    dir.setPath("/Library/Spelling/");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

    dir.setPath(QApplication::applicationDirPath());
    dir.cdUp();
    dir.cd("Resources");

    if (dir.isReadable()) {
        list.append(dir.path());
    }

#endif // ifdef Q_OS_MAC

    // qDebug() << list;
    return list;
}

//
//
// ---------------------------------------------------------------------------------------


void PLMUtils::Dir::createPath(QStringList paths)
{
    foreach(const QString path, paths) {
        QDir dir;

        dir.setPath(path);
        dir.mkpath(path);
    }
}

//
//
// ---------------------------------------------------------------------------------------


void PLMUtils::Dir::createPath(QString path)
{
    QStringList list;

    list.append(path);
    PLMUtils::Dir::createPath(list);
}

//
//
// ---------------------------------------------------------------------------------------


int PLMUtils::Misc::id;

QString PLMUtils::Misc::spaceInNumber(const QString numberString,
                                      const QString symbol)
{
    QString originalString = numberString;
    QString finalString;
    QStringList list;

    while (!originalString.isEmpty()) {
        list.append(originalString.right(3));
        originalString.chop(3);
    }

    while (!list.isEmpty()) {
        finalString.append(list.takeLast());
        finalString.append(symbol);
    }

    finalString.chop(symbol.size());
    return finalString;
}

//
//
// ---------------------------------------------------------------------------------------


//
//
// ---------------------------------------------------------------------------------------


//
//
// ---------------------------------------------------------------------------------------


//
//
// ---------------------------------------------------------------------------------------


//
//
// ---------------------------------------------------------------------------------------


QString PLMUtils::Lang::userLang;
QTranslator PLMUtils::Lang::userTranslator;

QString PLMUtils::Lang::getUserLang()
{
    return userLang;
}

void PLMUtils::Lang::setUserLang(const QString& value)
{
    userLang = value;
}

void PLMUtils::Lang::setUserLangFile(const QString& fileName)
{
    userTranslator.load(fileName);
}
