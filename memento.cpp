#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Класс, состояние которого мы будем сохранять
class Editor {
public:
    Editor(string text = "") : m_text(text) {}

    void setText(const string& text) {
        m_text = text;
    }

    string getText() const {
        return m_text;
    }

    // Создает Snapshot (Memento) для сохранения текущего состояния
    class Snapshot {
    public:
        Snapshot(const string& text) : m_text(text) {}

        string getText() const {
            return m_text;
        }

    private:
        string m_text;
    };

    // Создает Snapshot для сохранения текущего состояния
    Snapshot createSnapshot() const {
        return Snapshot(m_text);
    }

    // Восстанавливает состояние объекта из Snapshot
    void restoreSnapshot(const Snapshot& Snapshot) {
        m_text = Snapshot.getText();
    }

private:
    string m_text;
};

// Класс, который хранит историю состояний Editor
class History {
public:
    // Добавляет состояние в историю
    void addSnapshot(const Editor::Snapshot& snapshot) {
        m_history.push_back(snapshot);
    }

    // Возвращает последнее сохраненное состояние
    Editor::Snapshot getLastSnapshot() const {
        if (m_history.empty())
            throw logic_error("History is empty");
        return m_history.back();
    }

private:
    vector<Editor::Snapshot> m_history;
};

int main() {
    Editor editor("Hello, world!");
    History history;

    cout << editor.getText() << endl;

    // Сохраняем текущее состояние редактора
    history.addSnapshot(editor.createSnapshot());

    // Изменяем состояние редактора
    editor.setText("Goodbye, world!");

    cout << editor.getText() << endl;

    // Восстанавливаем предыдущее состояние
    editor.restoreSnapshot(history.getLastSnapshot());

    cout << editor.getText() << endl;
}

/*
Данный код демонстрирует реализацию паттерна Memento на языке C++.

Класс Editor представляет объект, состояние которого нужно сохранять и
восстанавливать. В данном случае, это текстовый редактор. Класс содержит
методы setText и getText для установки и получения текста соответственно.
Кроме того, класс содержит вложенный класс Snapshot, который используется
для сохранения состояния Editor. Метод createSnapshot создает объект Snapshot,
содержащий текущее состояние Editor, а метод restoreSnapshot позволяет
восстановить состояние из объекта Snapshot.

Класс History представляет объект, который хранит историю состояний Editor.
Он содержит методы addSnapshot и getLastSnapshot для добавления нового состояния
в историю и получения последнего сохраненного состояния соответственно.

В функции main создается объект Editor с начальным текстом "Hello, world!",
а также объект History для хранения истории состояний. Сначала текст редактора
выводится на экран, затем сохраняется текущее состояние с помощью метода
createSnapshot и изменяется текст на "Goodbye, world!". Затем состояние
восстанавливается из последнего сохраненного объекта Snapshot с помощью
метода restoreSnapshot, и текст снова выводится на экран.

Общая идея паттерна Memento состоит в том, чтобы сохранить состояние объекта
внешним объектом (Memento), чтобы потом можно было восстановить его состояние.
Этот подход позволяет сохранять и восстанавливать состояния объекта без нарушения
инкапсуляции и без доступа к приватным членам объекта. В данном случае, объект
Snapshot является Memento, который хранит состояние объекта Editor, а объект
History отвечает за хранение истории состояний.
*/

// https://refactoring.guru/ru/design-patterns/memento

/*
Снимок — это поведенческий паттерн проектирования, который позволяет сохранять
и восстанавливать прошлые состояния объектов, не раскрывая подробностей
их реализации.
*/