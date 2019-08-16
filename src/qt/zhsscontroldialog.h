// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2019 The HashShareCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZHSSCONTROLDIALOG_H
#define ZHSSCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zhss/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZHssControlDialog;
}

class CZHssControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZHssControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZHssControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZHssControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZHssControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZHssControlDialog(QWidget *parent);
    ~ZHssControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZHssControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZHssControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZHSSCONTROLDIALOG_H
