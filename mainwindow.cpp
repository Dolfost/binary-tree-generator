#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "food.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Binary tree generator");

    LOG("Hello, world!\n");

    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);

    ui->treeGraphicsView->setRenderHint(QPainter::Antialiasing);
    ui->treeGraphicsView->setScene(scene);

    tree = new bintree<nodeData>();

    // default tree
    tree->insert(15);
    tree->insert(7);
    tree->insert(23);
    tree->insert(3);
    tree->insert(11);
    tree->insert(19);
    tree->insert(27);
    tree->insert(5);
    tree->insert(17);
    tree->insert(21);
    tree->insert(25);

    printTree(tree);
    drawTree(tree);
}

void MainWindow::printTree(bintree<nodeData>* tree) {
    LOG("\nTrying to print the tree");
    if (tree->root != nullptr) {
        LOG("Tree is not empty. Printing...");
        QTreeWidgetItem* rootItem = new QTreeWidgetItem;
        rootItem->setText(0, "Binary search tree");
        ui->treeWidget->addTopLevelItem(rootItem);

        _printTree(tree->root, rootItem);
    }

}

void MainWindow::_printTree(node<nodeData>* leaf, QTreeWidgetItem* parentItem) {
    if (leaf != nullptr) {
        LOG("Non-NULL node were found. Adding it... ("+ QString::number(leaf->key) + ", " + leaf->data->str + ")");

        QTreeWidgetItem* childItem = new QTreeWidgetItem;
        childItem->setText(0, "- " + QString::number(leaf->key) + " " + leaf->data->str);
        parentItem->addChild(childItem);

        _printTree(leaf->left, childItem);
        _printTree(leaf->right, childItem);
    }
}

void MainWindow::drawTree(bintree<nodeData>* tree) {
    LOG("\nTrying to draw the tree...");
    if (tree->root != nullptr) {
        LOG("Tree is not empty. Drawing it");

        QGraphicsEllipseItem* rootEllipseItem = new QGraphicsEllipseItem;
        rootEllipseItem->setRect(0,0, 100, 40);
        rootEllipseItem->setBrush(QBrush(Qt::magenta));
        rootEllipseItem->setZValue(1);
        scene->addItem(rootEllipseItem);

        QGraphicsTextItem* textItem = new QGraphicsTextItem("Tree");
        textItem->setZValue(2);
        textItem->setPos(rootEllipseItem->boundingRect().center() - textItem->boundingRect().center());
        textItem->setDefaultTextColor(Qt::black);
        scene->addItem(textItem);

        QGraphicsRectItem* rootRectItem = new QGraphicsRectItem(rootEllipseItem->rect());

        _drawTree(tree->root, nullptr, rootRectItem, 0);
    }
}

#define dY 70
#define dX 60
#define sX 100
#define sY 40

void MainWindow::_drawTree(node<nodeData>* leaf, node<nodeData>* neighbor, QGraphicsRectItem* parentRectItem, int side) {
    if (leaf != nullptr) {
        LOG("Non-NULL node were found. Adding it... ("+ QString::number(leaf->key) + ", " + leaf->data->str + ")");

        QGraphicsRectItem* childRectItem = new QGraphicsRectItem;
        QGraphicsTextItem* labelItem = new QGraphicsTextItem(QString::number(leaf->key) + " " + leaf->data->str);
        QPen border;


        // if (side == -1) {
            // childRectItem->setRect(-(leftSpace + leaf->data->leftSpace + 2)*dX,
                               // parentRectItem->boundingRect().y() + dY, sX, sY);
        // } else if (side == 1) {
            // childRectItem->setRect((rightSpace + leaf->data->rightSpace + 2)*dX,
                               // parentRectItem->boundingRect().y() + dY, sX, sY);
        // } else if (side == 0) {
            // childRectItem->setRect(parentRectItem->boundingRect().x(), parentRectItem->boundingRect().y() + dY, sX, sY);
        //

        // HOW TO CALCULATE X OF NODE??? Send you'r algorithm versions to rehanvladyslav@gmail.com
        if (side == -1) {
            childRectItem->setRect(parentRectItem->boundingRect().x() - (bintree<nodeData>::rightDepth(leaf) + bintree<nodeData>::leftDepth(neighbor) + 2)*dX,
                               parentRectItem->boundingRect().y() + dY, sX, sY);
        } else if (side == 1) {
            childRectItem->setRect(parentRectItem->boundingRect().x() + (bintree<nodeData>::rightDepth(neighbor) + bintree<nodeData>::leftDepth(leaf) + 2)*dX,
                               parentRectItem->boundingRect().y() + dY, sX, sY);
        } else if (side == 0) {
            childRectItem->setRect(parentRectItem->boundingRect().x(), parentRectItem->boundingRect().y() + dY, sX, sY);
        }

        // if (side == -1) {
            // childRectItem->setRect(parentRectItem->boundingRect().x() - dX,
                               // parentRectItem->boundingRect().y() + dY, sX, sY);
        // } else if (side == 1) {
            // childRectItem->setRect(parentRectItem->boundingRect().x() + dX,
                               // parentRectItem->boundingRect().y() + dY, sX, sY);
        // } else if (side == 0) {
            // childRectItem->setRect(parentRectItem->boundingRect().x(), parentRectItem->boundingRect().y() + dY, sX, sY);
        // }

        // if (side == -1) {
            // childRectItem->setRect(parentRectItem->boundingRect().x() - (pow(2, depth))*dX,
                               // parentRectItem->boundingRect().y() + dY, sX, sY);
        // } else if (side == 1) {
            // childRectItem->setRect(parentRectItem->boundingRect().x() + (pow(2, depth))*dX,
                               // parentRectItem->boundingRect().y() + dY, sX, sY);
        // } else if (side == 0) {
            // childRectItem->setRect(parentRectItem->boundingRect().x(), parentRectItem->boundingRect().y() + dY, sX, sY);
        // }

        labelItem->setPos(childRectItem->boundingRect().center() - labelItem->boundingRect().center());
        labelItem->setDefaultTextColor(Qt::white);

        childRectItem->setBrush(QBrush(Qt::red));

        if (leaf == lastFoundMax) {
            childRectItem->setBrush(QBrush(Qt::green));
            labelItem->setDefaultTextColor(Qt::black);
        } else if (leaf == lastFoundMin) {
            childRectItem->setBrush(QBrush(Qt::cyan));
            labelItem->setDefaultTextColor(Qt::black);
        } else {
            childRectItem->setBrush(QBrush(Qt::red));
            labelItem->setDefaultTextColor(Qt::white);
        }

        if (leaf == lastFound) {
            border.setColor(Qt::yellow);
            border.setWidth(3);
        }

        childRectItem->setPen(border);

        QGraphicsLineItem* lineItem = new QGraphicsLineItem(parentRectItem->boundingRect().center().x(),
                                                            parentRectItem->boundingRect().center().y(),
                                                            childRectItem->boundingRect().center().x(),
                                                            childRectItem->boundingRect().center().y());
        lineItem->setPen(QPen(Qt::white));

        lineItem->setZValue(0);
        childRectItem->setZValue(1);
        labelItem->setZValue(2);

        scene->addItem(lineItem);
        scene->addItem(childRectItem);
        scene->addItem(labelItem);

        _drawTree(leaf->left, leaf->right, childRectItem, -1);
        _drawTree(leaf->right, leaf->left, childRectItem, 1);
    }
}

bintree<nodeData>* MainWindow::makeTree(void) {
    delete tree;

    tree = new bintree<nodeData>;

    int count = ui->nodeQuantitySpinBox->value();
    int max = ui->maxKeySpinBox->value();

    node<nodeData>* node;
    for (int i = 0; i < count; i++) {
        node = tree->insert(QRandomGenerator::global()->bounded(max+1));
        if (ui->addTextCheckBox->isChecked())
            node->data->str = food[QRandomGenerator::global()->bounded(FOOD_SIZE+1)];
    }

    onTreeOperation();

    return tree;
}

void MainWindow::updateTree() {
    LOG("\nRefreshing the view.");

    ui->treeWidget->clear();
    scene->clear();

    if (tree == nullptr)
        QMessageBox::critical(this, "Error", "The list is not created.");
    else {
        printTree(tree);
        drawTree(tree);
        scene->setSceneRect(scene->itemsBoundingRect());
    }

    ui->treeWidget->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTreeOperation(bool changing) {
    if (changing) {
        lastFoundMax = nullptr;
        lastFoundMin = nullptr;
        lastFound = nullptr;

        ui->maxLabel->setText("???");
        ui->minLabel->setText("???");
        ui->findLabel->setText("???");
    }

    if (ui->findAutomaticallyCheckBox->isChecked()) {
        findMaxNode(false);
        findMinNode(false);
    }

    if (ui->refreshAutomaticallyCheckBox->isChecked()) {
        LOG("\nRefreshing thee tree because the refresh automatically box is ckecked.");
        updateTree();
    }
}

void MainWindow::on_expandAllPushButton_clicked()
{
    LOG("\nExpanded all.");
    ui->treeWidget->expandAll();
}


void MainWindow::on_collapseAllPushButton_clicked()
{
    LOG("\nCollapsed all.");
    ui->treeWidget->collapseAll();
}

void MainWindow::on_createButton_clicked()
{
    LOG("\nRegenerating the tree...");
    makeTree();
}


void MainWindow::on_refreshButton_clicked()
{
    LOG("\nRefreshing the view...");
    updateTree();
}

void MainWindow::on_expandToLevelPushButton_clicked()
{
    LOG("\nExpanding to level...");
    ui->treeWidget->expandToDepth(ui->expandToLevelSpinBox->value());
}

void MainWindow::on_insertButton_clicked()
{
    LOG("Insert button were clicked. Inserting node wiht key " + QString::number(ui->insertKeySpinBox->value()));

    node<nodeData>* node = tree->insert(ui->insertKeySpinBox->value());

    if (node != nullptr) {
        node->data->str = ui->textDataTextBox->text();
    }

    onTreeOperation();
}

void MainWindow::on_deleteButton_clicked()
{
    LOG("Tryint to delete node with key " + QString::number(ui->insertKeySpinBox->value()));


    if (tree->search(ui->insertKeySpinBox->value()) == nullptr) {
        LOG("Couldn't delete node with key " + QString::number(ui->insertKeySpinBox->value()) + ".");
        QMessageBox::critical(this, "Could not delete node", "Couldn't delete node with key " + QString::number(ui->insertKeySpinBox->value()) + ".");
        return;
    } else
        tree->destroy(ui->insertKeySpinBox->value());

    LOG("Node was deleted successfully!");

    onTreeOperation();
}

void MainWindow::on_findMaxKeypushButton_clicked()
{
    LOG("\nFind max key button were pressed.");
    findMaxNode();
}

void MainWindow::on_insertKeySpinBox_valueChanged(int arg1)
{
    ui->deleteButton->setText("Delete node with key " + QString::number(arg1));
}


void MainWindow::on_findMinKeypushButton_clicked()
{
    LOG("\nFind min key button were pressed.");
    findMinNode();

}

void MainWindow::findMaxNode(bool update) {
    LOG("Trying to find max key.");

    node<nodeData>* leaf = tree->searchMax();

    if (leaf != nullptr) {
        LOG("Max key found (" + QString::number(leaf->key) + ").");

        lastFoundMax = leaf;

        ui->maxLabel->setText(QString::number(leaf->key));
        if (update)
            onTreeOperation(false);
    } else {
        LOG("Max key could not be found.");

        QMessageBox::critical(this, "Could not find node", "Couldn't find max value node.");

        ui->maxLabel->setText("???");
    }
}

void MainWindow::findMinNode(bool update) {
    LOG("Trying to find min key.");

    node<nodeData>* leaf = tree->searchMin();

    if (leaf != nullptr) {
        LOG("Min key found (" + QString::number(leaf->key) + ").");

        lastFoundMin = leaf;

        ui->minLabel->setText(QString::number(leaf->key));
        if (update)
            onTreeOperation(false);
    } else {
        LOG("Min key could not be found.");

        QMessageBox::critical(this, "Could not find node", "Couldn't find min value node.");

        ui->maxLabel->setText("???");
    }
}

void MainWindow::on_findNodePushButton_clicked()
{
    LOG("Trying to find node with key " + QString::number(ui->findKeySpinBox->value()) + ".");

    node<nodeData>* leaf = tree->search(ui->findKeySpinBox->value());

    if (leaf != nullptr) {
        LOG("Node were found.");

        lastFound = leaf;

        ui->findLabel->setText(leaf->data->str);
        onTreeOperation(false);
    } else {
        LOG("Node could not be found");

        QMessageBox::critical(this, "Could not find node", "Couldn't find node with key " + QString::number(ui->findKeySpinBox->value()) + ".");

        ui->findLabel->setText("???");
    }
}

void MainWindow::on_findAutomaticallyCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->findMaxKeypushButton->setEnabled(false);
        ui->findMaxKeypushButton->setCursor(Qt::CursorShape::ForbiddenCursor);
        ui->findMinKeypushButton->setEnabled(false);
        ui->findMinKeypushButton->setCursor(Qt::CursorShape::ForbiddenCursor);
        findMaxNode(false);
        findMinNode();
    } else {
        onTreeOperation();
        ui->findMaxKeypushButton->setEnabled(true);
        ui->findMaxKeypushButton->setCursor(Qt::CursorShape::PointingHandCursor);
        ui->findMinKeypushButton->setEnabled(true);
        ui->findMinKeypushButton->setCursor(Qt::CursorShape::PointingHandCursor);
    }
}

void MainWindow::on_refreshAutomaticallyCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->refreshButton->setEnabled(false);
        ui->refreshButton->setCursor(Qt::CursorShape::ForbiddenCursor);
        onTreeOperation(false);
    } else {
        ui->refreshButton->setEnabled(true);
        ui->refreshButton->setCursor(Qt::CursorShape::PointingHandCursor);
    }

}

void MainWindow::on_findKeySpinBox_valueChanged(int arg1)
{
    ui->findNodePushButton->setText("Find node with key " + QString::number(arg1));
}

void MainWindow::on_zoomHorizontalSlider_valueChanged(int value)
{
    qreal factor = value / 100.0;
    ui->treeGraphicsView->setTransform(QTransform::fromScale(factor, factor));

    ui->zoomLabel->setText("Zoom: " + QString::number(value) + "%");
}
