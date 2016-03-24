#include "settings.h"
#include "connection.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


map<string, string> Settings::_settings;
list<int> Settings::_synchronizingIndices;


Settings::Settings() {
    connect(
        &Connection::instance(),
        &Connection::connected,
        this,
        &Settings::clear
    );
	connect(
		&Connection::instance(),
		&Connection::connected,
		&Connection::instance(),
        &Connection::settingsRequest
	);
	connect(
		&Connection::instance(),
		&Connection::settingReceived,
		this,
        &Settings::set
	);
    MainWindow::ui().settingsTableView->setModel( this );
}

Settings::~Settings() {
}

Settings &Settings::instance() {
    static Settings instance;
    return instance;
}

string Settings::getKey(const int index) {
    std::map<string,string>::iterator iterator = _settings.begin();
    std::advance(iterator, index);
    return iterator->first;
}

string Settings::getValue(const int index) {
    std::map<string,string>::iterator iterator = _settings.begin();
    std::advance(iterator, index);
    return iterator->second;
}

int Settings::getIndex(const string& key) {
    std::map<string,string>::iterator iterator = _settings.find(key);
    return std::distance( _settings.begin(), _settings.find(key) );
}

void Settings::set( const string& key, const string& value ) {
    qDebug() << "Settings::set()" << QString::fromStdString(key) << QString::fromStdString(value);
    if( _settings.find(key) == _settings.end() ) {
        instance().beginInsertRows( QModelIndex(), _settings.size(), _settings.size() );
        instance().endInsertRows();
        _settings[ key ] = value;
    } else {
        _synchronizingIndices.remove( getIndex(key) );
        _settings[ key ] = value;
        emit instance().dataChanged( instance().index( getIndex(key), 0, QModelIndex()), instance().index( getIndex(key), 1, QModelIndex()) );
    }
}

void Settings::remove( const string& key ) {
    if( _settings.find(key) != _settings.end() ) {
        instance().beginRemoveRows( QModelIndex(), getIndex(key), getIndex(key) );
        _settings.erase( _settings.find( key ) );
        instance().endRemoveRows();
    }
}

void Settings::clear() {
    if( _settings.size() ) {
        instance().beginRemoveRows( QModelIndex(), 0, _settings.size()-1 );
        _settings.clear();
        instance().endRemoveRows();
    }
}

bool Settings::setData(const QModelIndex& index, const QVariant& value, int role) {
    if( role == Qt::EditRole ) {
        Connection::instance().settingsSend( getKey( index.row() ), value.toString().toStdString() );
        _synchronizingIndices.insert( _synchronizingIndices.end(), index.row() );
    }
    return false;
}

Qt::ItemFlags Settings::flags(const QModelIndex& index) const {
    if( index.column() == 1 ) {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    } else {
        return Qt::ItemIsSelectable;
    }
}

int Settings::rowCount(const QModelIndex &parent) const {
    return _settings.size();
}

int Settings::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant Settings::data(const QModelIndex &index, int role) const {
    switch( role ) {
        case Qt::DisplayRole:
            if( index.row() < _settings.size() ) {
                typedef std::map<std::string, std::map<std::string, std::string>>::iterator it_type;
                int i=0;
                for( map< string, string>::iterator iterator = _settings.begin(); iterator != _settings.end(); iterator++) {
                    if( i++ == index.row() ) {
                        switch( index.column() ) {
                            case 0:
                                return QString::fromStdString( iterator->first );
                            case 1:
                                return QString::fromStdString( iterator->second );
                        }
                    }
                }
            }
            break;
        case Qt::BackgroundColorRole:
            if( find( _synchronizingIndices.begin(), _synchronizingIndices.end(), index.row() ) != _synchronizingIndices.end() ) {
                return QVariant(QBrush(QColor(255,248,220)));
            } else {
                return QVariant(QBrush(Qt::white));
            }
            break;
    }
	return QVariant();
}

QVariant Settings::headerData(int section, Qt::Orientation orientation, int role) const {
	if( role == Qt::DisplayRole ) {
		if( orientation == Qt::Horizontal ) {
			switch( section ) {
				case 0:
					return QString("Name");
				case 1:
					return QString("Value");
			}
		}
	}
	return QVariant();
}

