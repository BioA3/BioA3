// Copyright (c) 2019 The BIOA3 developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLBIOA3WIDGET_H
#define COINCONTROLBIOA3WIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlBioA3Widget;
}

class CoinControlBioA3Widget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlBioA3Widget(QWidget *parent = nullptr);
    ~CoinControlBioA3Widget();

private:
    Ui::CoinControlBioA3Widget *ui;
};

#endif // COINCONTROLBIOA3WIDGET_H
