#include <iostream>
#include <string>

class GameObject {
public:
    explicit GameObject(int id) : id(id) { };

    virtual ~GameObject() = 0;

    int getID() const {
        return id;
    }

    virtual void print() const {
        std::cout << "ID: " << id << std::endl;
    }

protected:
    int id;


};

GameObject::~GameObject() {}


class PhysicalObject : public GameObject {
public:
    PhysicalObject(int id, int weight) : GameObject(id), weight(weight) { };

    virtual ~PhysicalObject() = 0;

    int getWeight() const {
        return weight;
    }

    void print() const override {
        std::cout << "Weight: " << weight << std::endl;
        GameObject::print();
    }

protected:
    int weight;
};

PhysicalObject::~PhysicalObject() {}


class GraphicObject : public GameObject {
public:
    GraphicObject(int id, std::string texture) : GameObject(id), texture(texture) { };

    virtual ~GraphicObject() = 0;

    std::string getTexture() const {
        return texture;
    }

    void print() const override {
        std::cout << "Texture: " << texture << std::endl;
        GameObject::print();
    }

protected:
    std::string texture;
};

GraphicObject::~GraphicObject() {}

class Bullet : public PhysicalObject {
public:
    Bullet(int id, int caliber, int weight) : PhysicalObject(id, weight), caliber(caliber) {}

    ~Bullet() {}

    int getCaliber() const {
        return caliber;
    }

    void print() const override {
        std::cout << "-----\nBullet" << std::endl;
        std::cout << "Caliber: " << getCaliber() << std::endl;
        PhysicalObject::print();
        std::cout << "-----" << std::endl;
    }

private:
    int caliber;
};

class Vehicle : public PhysicalObject {
public:
    Vehicle(int id, int weight, int enginePower) : PhysicalObject(id, weight), enginePower(enginePower) {}

    ~Vehicle() {}

    int getEnginePower() const {
        return enginePower;
    }

    void print() const override {
        std::cout << "Engine Power: " << getEnginePower() << std::endl;
        PhysicalObject::print();
    }

protected:
    int enginePower;
};

class Tank : public Vehicle, public GraphicObject {
public:
    Tank(int id, int armorThickness, int enginePower, int weight, std::string texture) : Vehicle(id, weight, enginePower), GraphicObject(id, texture), armorThickness(armorThickness) {}

    ~Tank() {}

    int getArmorThickness() const {
        return armorThickness;
    }

    void print() const override {
        std::cout << "-----\nTank" << std::endl;
        std::cout << "Armor Thickness: " << getArmorThickness() << std::endl;
        std::cout << "Texture: " << getTexture() << std::endl;
        Vehicle::print();
        std::cout << "-----" << std::endl;
    }
private:
    int armorThickness;
};

class Aircraft : public Vehicle, public GraphicObject {
public:
    Aircraft(int id, int loadCapacity, int enginePower, int weight, std::string texture) : Vehicle(id, weight, enginePower), GraphicObject(id, std::move(texture)), loadCapacity(loadCapacity) {}

    ~Aircraft() {}

    int getLoadCapacity() const {
        return loadCapacity;
    }

    void print() const override {
        std::cout << "-----\nAircraft" << std::endl;
        std::cout << "Load Capacity: " << getLoadCapacity() << std::endl;
        std::cout << "Texture: " << getTexture() << std::endl;
        Vehicle::print();
        std::cout << "-----" << std::endl;
    }
private:
    int loadCapacity;
};

template<class T>
class BinaryTreeNode {
public:
    explicit BinaryTreeNode(T value) : value(value), left(nullptr), right(nullptr) {}
    T value;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
};

template<class T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        clear(root);
    }

    void insert(T value) {
        if (root == nullptr) {
            root = new BinaryTreeNode<T>(value);
        } else {
            insertNode(root, value);
        }
    }

    void remove(int k) {
        root = removeNode(root, k);
    }

    void printInOrder() {
        printInOrder(root);
    }

    void printPreOrder() {
        printPreOrder(root);
    }

    void printPostOrder() {
        printPostOrder(root);
    }

    void print() const {
        print(root);
    }

    void print(GameObject *object) const {
        object->print();
    }
private:
    BinaryTreeNode<T>* root;

    BinaryTreeNode<T>* insertNode(BinaryTreeNode<T>* node, T v) {
        if (node == nullptr) {
            return new BinaryTreeNode<T>(v);
        }
        if (v->getID() < node->value->getID()) {
            node->left = insertNode(node->left, v);
        }
        else if (v->getID() > node->value->getID()) {
            node->right = insertNode(node->right, v);
        }
        else {
            std::cout << "Object with ID " << v->getID() << " already exists." << std::endl;
            node->value->print();
        }
        return node;
    }

    BinaryTreeNode<T>* removeNode(BinaryTreeNode<T>* node, int k) {
        if (node == nullptr) {
            return node;
        }
        if (k < node->value->getID()) {
            node->left = removeNode(node->left, k);
        }
        else if (k > node->value->getID()) {
            node->right = removeNode(node->right, k);
        }
        else {
            if (node->left == nullptr) {
                BinaryTreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BinaryTreeNode<T> *temp = node->left;
                delete node;
                return temp;
            }
            else {
                BinaryTreeNode<T>* temp = minNode(node->right);
                node->value = temp->value;
                node->right = removeNode(node->right, temp->value->getID());
            }
        }
        return node;
    }

    BinaryTreeNode<T>* minNode(BinaryTreeNode<T>* node) {
        BinaryTreeNode<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void clear(BinaryTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void printInOrder(BinaryTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        node->value->print();
        printInOrder(node->right);
    }

    void printPreOrder(BinaryTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        node->value->print();
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    void printPostOrder(BinaryTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        printPostOrder(node->left);
        printPostOrder(node->right);
        node->value->print();
    }
};

int main() {
    BinaryTree<GameObject*> bt;

    // Console interface
    while (true) {
        std::cout << "1. Insert new object" << std::endl;
        std::cout << "2. Remove object" << std::endl;
        std::cout << "3. Print objects" << std::endl;
        std::cout << "4. Exit" << std::endl;
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cout << "1. Bullet" << std::endl;
                std::cout << "2. Tank" << std::endl;
                std::cout << "3. Aircraft" << std::endl;
                int choiceType;
                std::cin >> choiceType;

                int id, caliber, weight, enginePower;
                std::string texture;

                switch (choiceType) {
                    case 1:
                        std::cout << "Enter ID: ";
                        std::cin >> id;
                        std::cout << "Enter caliber: ";
                        std::cin >> caliber;
                        std::cout << "Enter weight: ";
                        std::cin >> weight;
                        bt.insert(static_cast<GameObject *>(new Bullet(id, caliber, weight)));
                        break;
                    case 2:
                        int armour;
                        std::cout << "Enter ID: ";
                        std::cin >> id;
                        std::cout << "Enter armourt: ";
                        std::cin >> armour;
                        std::cout << "Enter engine power: ";
                        std::cin >> enginePower;
                        std::cout << "Enter weight: ";
                        std::cin >> weight;
                        std::cout << "Enter texture: ";
                        std::cin >> texture;
                        bt.insert(static_cast<Vehicle *>(new Tank(id, armour, enginePower, weight, texture)));
                        break;
                    case 3:
                        int loadCapacity;
                        std::cout << "Enter ID: ";
                        std::cin >> id;
                        std::cout << "Enter load capacity: ";
                        std::cin >> loadCapacity;
                        std::cout << "Enter engine power: ";
                        std::cin >> enginePower;
                        std::cout << "Enter weight: ";
                        std::cin >> weight;
                        std::cout << "Enter texture: ";
                        std::cin >> texture;
                        bt.insert(static_cast<Vehicle *>(new Aircraft(id, loadCapacity, enginePower, weight, texture)));
                        break;
                    default:
                        std::cout << "Wrong choice" << std::endl;
                        break;
                }
                }
                break;
            case 2:
                int id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                bt.remove(id);
                break;
            case 3:
                std::cout << "1. In-order" << std::endl;
                std::cout << "2. Pre-order" << std::endl;
                std::cout << "3. Post-order" << std::endl;
                int choicePrint;
                std::cin >> choicePrint;
                if (choicePrint == 1) {
                    bt.printInOrder();
                }
                else if (choicePrint == 2) {
                    bt.printPreOrder();
                }
                else if (choicePrint == 3) {
                    bt.printPostOrder();
                }
                break;
            case 4:
                return 0;
            default:
                std::cout << "Wrong input" << std::endl;
        }
    }
    return 0;
}
