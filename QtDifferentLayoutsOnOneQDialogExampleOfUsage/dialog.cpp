#include <QtWidgets>
#include "dialog.h"

Dialog::Dialog()
{
    createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Basic Layouts"));

    //connect(buttons[0], &QPushButton::clicked, this, &Dialog::onButton1clicked);
    for(int i=0; i<NumButtons; ++i)
    {
        connect(buttons[i], &QPushButton::clicked, [this, i](){
            QMessageBox::information(this, "Button clicked", QString("Button %1 clicked").arg(i+1));
        });
    }
}

void Dialog::onButton1clicked()
{
    QMessageBox::information(this, "Button clicked", "Button 1 clicked");
}

// See here: https://stackoverflow.com/questions/26791102/qt-use-of-in-tr

//As far as tr is concerned & is just another character in the string
//and has no special meaning. However it does have a special meaning
//to QAction: It sets the following character as the entry's shortcut
//within a menu, so when you have the "File" menu open, pressing the n
//key will activate the "New" entry, x will active "Exit" and so on.
//Depending on the OS, the character after the & may also be underlined
//(on Windows it's only underlined when you press the Alt key).

//& is used to indicate a character that should be used for the
//Alt-key shortcut for a given menu item. Assuming these actions
//are being put into a menu named &File, pressing Alt-F, then N
//would activate the New action.

void Dialog::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"), this);
    //PRESS Alt + F AND THEN x will lead to an exit:
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
    QHBoxLayout *layout = new QHBoxLayout;
    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
        layout->addWidget(buttons[i]);
    }
    horizontalGroupBox->setLayout(layout);
}

void Dialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid layout"));
    QGridLayout *layout = new QGridLayout;
    for (int i = 0; i < NumGridRows; ++i) {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        lineEdits[i] = new QLineEdit;
        lineEdits[i]->setPlaceholderText(QString("String %1").arg(i+1));
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }
    smallEditor = new QTextEdit;
//    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
//                                 "grid layout."));
    smallEditor->setPlaceholderText(tr("This widget takes up about two thirds of the "
                                       "grid layout."));
    layout->addWidget(smallEditor, 0, 2, 4, 1);
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void Dialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    QLineEdit * lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("Type Your name here");
    layout->addRow(new QLabel(tr("Line 1:")), lineEdit);
    QComboBox * combo = new QComboBox;
    combo->addItem("Student");
    combo->addItem("Tutor");
    layout->addRow(new QLabel(tr("Line 2, long text:")), combo);
    QSpinBox * spin = new QSpinBox;
    spin->setValue(10);
    layout->addRow(new QLabel(tr("Line 3:")), spin);
    formGroupBox->setLayout(layout);
}

