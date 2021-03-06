#include "skrstathub.h"
#include "plmdata.h"

SKRStatHub::SKRStatHub(QObject *parent) : QObject(parent)
{
    connect(plmdata->sheetHub(), &PLMPaperHub::wordCountChanged,      this, &SKRStatHub::updateWordStats);
    connect(plmdata->noteHub(),  &PLMPaperHub::wordCountChanged,      this, &SKRStatHub::updateWordStats);
    connect(plmdata->sheetHub(), &PLMPaperHub::characterCountChanged, this, &SKRStatHub::updateCharacterStats);
    connect(plmdata->noteHub(),  &PLMPaperHub::characterCountChanged, this, &SKRStatHub::updateCharacterStats);

    connect(plmdata->sheetHub(), &PLMPaperHub::trashedChanged,        this, &SKRStatHub::setSheetTrashed);
    connect(plmdata->noteHub(),  &PLMPaperHub::trashedChanged,        this, &SKRStatHub::setNoteTrashed);

    connect(plmdata->sheetHub(), &PLMPaperHub::paperRemoved,          this, &SKRStatHub::removeSheetFromStat);
    connect(plmdata->noteHub(),  &PLMPaperHub::paperRemoved,          this, &SKRStatHub::removeNoteFromStat);
}

int SKRStatHub::getSheetTotalCount(SKRStatHub::StatType type, int project)
{
    int totalCount                             = 0;
    QHash<int, QHash<QString, int> > paperHash = m_sheetHashByProjectHash.value(project,
                                                                                QHash<int, QHash<QString, int> >());

    QHash<int, QHash<QString, int> >::const_iterator i = paperHash.constBegin();

    while (i != paperHash.constEnd()) {
        QHash<QString, int> hash = i.value();

        if (!hash.value("isTrashed", 0)) {
            switch (type) {
            case SKRStatHub::Character:
                totalCount += hash.value("characterCount", 0);
                break;

            case SKRStatHub::Word:
                totalCount += hash.value("wordCount", 0);
                break;
            }
        }
        ++i;
    }

    return totalCount;
}

// ---------------------------------------------------------------------------------

int SKRStatHub::getNoteTotalCount(SKRStatHub::StatType type, int project)
{
    int totalCount                             = 0;
    QHash<int, QHash<QString, int> > paperHash = m_noteHashByProjectHash.value(project,
                                                                               QHash<int, QHash<QString, int> >());

    QHash<int, QHash<QString, int> >::const_iterator i = paperHash.constBegin();

    while (i != paperHash.constEnd()) {
        QHash<QString, int> hash = i.value();

        if (!hash.value("isTrashed", 0)) {
            switch (type) {
            case SKRStatHub::Character:
                totalCount += hash.value("characterCount", 0);
                break;

            case SKRStatHub::Word:
                totalCount += hash.value("wordCount", 0);
                break;
            }
        }
        ++i;
    }

    return totalCount;
}

// ---------------------------------------------------------------------------------

void SKRStatHub::updateWordStats(SKR::ItemType paperType, int projectId, int paperId, int wordCount, bool triggerProjectModifiedSignal)
{
    QHash<int, QHash<QString, int> > projectHash;
    PLMPropertyHub *propertyHub = nullptr;
    PLMPaperHub    *paperHub    = nullptr;

    if (paperType == SKR::Note) {
        projectHash = m_noteHashByProjectHash.value(projectId);
        propertyHub = plmdata->notePropertyHub();
        paperHub    = plmdata->noteHub();
    }
    else if (paperType == SKR::Sheet) {
        projectHash = m_sheetHashByProjectHash.value(projectId);
        propertyHub = plmdata->sheetPropertyHub();
        paperHub    = plmdata->sheetHub();
    }

    // ------------- get trashed
    bool isTrashed = paperHub->getTrashed(projectId, paperId);

    // ------------- update word_count

    if (wordCount != -1) {
        propertyHub->setProperty(projectId, paperId, "word_count", QString::number(wordCount), true, triggerProjectModifiedSignal);
    }

    // ------------- update general stats

    QHash<QString, int> paperHash = projectHash.value(paperId);

    if (wordCount != -1) {
        paperHash.insert("wordCount", wordCount);
    }
    paperHash.insert("isTrashed", isTrashed);
    projectHash.insert(paperId, paperHash);

    int totalCount = 0;

    if (paperType == SKR::Note) {
        m_noteHashByProjectHash.insert(projectId, projectHash);
        totalCount = getNoteTotalCount(SKRStatHub::Word, projectId);
    }
    else if (paperType == SKR::Sheet) {
        m_sheetHashByProjectHash.insert(projectId, projectHash);
        totalCount = getSheetTotalCount(SKRStatHub::Word, projectId);
    }

    emit statsChanged(SKRStatHub::Word, paperType, projectId, totalCount);


    // -------------update parents' charCountWithChildren:

    // get all ancestors
    QList<int> ancestors = paperHub->getAllAncestors(projectId, paperId);

    ancestors.prepend(paperId);

    // for each ancestor, get all children

    for (int ancestorId : ancestors) {
        QList<int> children = paperHub->getAllChildren(projectId, ancestorId);

        // remove trashed
        QMutableListIterator<int> i(children);

        while (i.hasNext()) {
            int childId                   = i.next();
            QHash<QString, int> childHash = projectHash.value(childId, QHash<QString, int>());

            if (childHash.value("isTrashed", 0)) {
                i.remove();
            }
        }

        int totalChildrenCount = 0;

        for (int childId : children) {
            QHash<QString, int> childHash = projectHash.value(childId, QHash<QString, int>());

            totalChildrenCount += childHash.value("wordCount", 0);
        }

        // add ancestor count
        QHash<QString, int> ancestorHash = projectHash.value(ancestorId, QHash<QString, int>());
        totalChildrenCount += ancestorHash.value("wordCount", 0);

        // set property

        propertyHub->setProperty(projectId, ancestorId, "word_count_with_children",
                                 QString::number(totalChildrenCount), true, triggerProjectModifiedSignal);
    }
}

// ---------------------------------------------------------------------------------

void SKRStatHub::updateCharacterStats(SKR::ItemType paperType, int projectId, int paperId, int characterCount, bool triggerProjectModifiedSignal)
{
    QHash<int, QHash<QString, int> > projectHash;
    PLMPropertyHub *propertyHub = nullptr;
    PLMPaperHub    *paperHub    = nullptr;

    if (paperType == SKR::Note) {
        projectHash = m_noteHashByProjectHash.value(projectId);
        propertyHub = plmdata->notePropertyHub();
        paperHub    = plmdata->noteHub();
    }
    else if (paperType == SKR::Sheet) {
        projectHash = m_sheetHashByProjectHash.value(projectId);
        propertyHub = plmdata->sheetPropertyHub();
        paperHub    = plmdata->sheetHub();
    }

    // ------------- get trashed
    bool isTrashed = paperHub->getTrashed(projectId, paperId);

    // ------------- update char_count

    if (characterCount != -1) {
        propertyHub->setProperty(projectId, paperId, "char_count", QString::number(characterCount), true, triggerProjectModifiedSignal);
    }

    // ------------- update general stats

    QHash<QString, int> paperHash = projectHash.value(paperId);

    if (characterCount != -1) {
        paperHash.insert("characterCount", characterCount);
    }

    paperHash.insert("isTrashed", isTrashed);
    projectHash.insert(paperId, paperHash);

    int totalCount = 0;

    if (paperType == SKR::Note) {
        m_noteHashByProjectHash.insert(projectId, projectHash);
        totalCount = getNoteTotalCount(SKRStatHub::Character, projectId);
    }
    else if (paperType == SKR::Sheet) {
        m_sheetHashByProjectHash.insert(projectId, projectHash);
        totalCount = getSheetTotalCount(SKRStatHub::Character, projectId);
    }

    emit statsChanged(SKRStatHub::Character, paperType, projectId, totalCount);

    // -------------update parents' charCountWithChildren:

    // get all ancerstors
    QList<int> ancestors = paperHub->getAllAncestors(projectId, paperId);

    ancestors.prepend(paperId);

    // for each ancestor, get all children

    for (int ancestorId : ancestors) {
        QList<int> children = paperHub->getAllChildren(projectId, ancestorId);

        // remove trashed
        QMutableListIterator<int> i(children);

        while (i.hasNext()) {
            int childId                   = i.next();
            QHash<QString, int> childHash = projectHash.value(childId, QHash<QString, int>());

            if (childHash.value("isTrashed", 0)) {
                i.remove();
            }
        }

        int totalChildrenCount = 0;

        for (int childId : children) {
            QHash<QString, int> childHash = projectHash.value(childId, QHash<QString, int>());

            totalChildrenCount += childHash.value("characterCount", 0);
        }

        // add ancestor count
        QHash<QString, int> ancestorHash = projectHash.value(ancestorId, QHash<QString, int>());
        totalChildrenCount += ancestorHash.value("characterCount", 0);

        // set property

        propertyHub->setProperty(projectId, ancestorId, "char_count_with_children",
                                 QString::number(totalChildrenCount), true, triggerProjectModifiedSignal);
    }
}

// ---------------------------------------------------------------------------------

void SKRStatHub::setSheetTrashed(int projectId, int sheetId, bool isTrashed)
{
    Q_UNUSED(isTrashed)
    updateCharacterStats(SKR::Sheet, projectId, sheetId);
    updateWordStats(SKR::Sheet, projectId, sheetId);
}

// ---------------------------------------------------------------------------------

void SKRStatHub::setNoteTrashed(int projectId, int noteId, bool isTrashed)
{
    Q_UNUSED(isTrashed)
    updateCharacterStats(SKR::Note, projectId, noteId);
    updateWordStats(SKR::Note, projectId, noteId);
}

// ---------------------------------------------------------------------------------

void SKRStatHub::removeSheetFromStat(int projectId, int sheetId)
{
    // if not done, trash it, needed for cleaner calculation
    setSheetTrashed(projectId, sheetId, true);

    // delete ref to paperId
    QHash<int, QHash<QString, int> > projectHash = m_sheetHashByProjectHash.value(projectId);

    projectHash.remove(sheetId);
    m_sheetHashByProjectHash.insert(projectId, projectHash);
}

// ---------------------------------------------------------------------------------

void SKRStatHub::removeNoteFromStat(int projectId, int noteId)
{
    // if not done, trash it, needed for cleaner calculation
    setNoteTrashed(projectId, noteId, true);

    // delete ref to paperId
    QHash<int, QHash<QString, int> > projectHash = m_noteHashByProjectHash.value(projectId);

    projectHash.remove(noteId);
    m_noteHashByProjectHash.insert(projectId, projectHash);
}
