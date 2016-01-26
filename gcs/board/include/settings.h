#ifndef	SETTINGS_H
#define	SETTINGS_H


#include <QAbstractTableModel>
#include <map>
#include <queue>


using namespace std;


class Settings : public QAbstractTableModel {
    private:
                                    Settings();
                                   ~Settings();
    public:
        static Settings&            instance();
        static string               getKey(int index);
        static string               getValue(int index);
        static int                  getIndex(const string& key);

        //static void                 init();
        //static void                 sync();
        static void                 set( const string& name, const string& value );
        //static string               get( const string& );
        static void                 remove( const string& );
        static void                 clear();
        //static map<string, string>& settings();

        bool                        setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
        Qt::ItemFlags               flags(const QModelIndex& index) const;
        int                         rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
        int                         columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        QVariant                    data(const QModelIndex &index, int role ) const Q_DECL_OVERRIDE;
        QVariant                    headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    private:
        static map<string, string>  _settings;
        static list<int>            _synchronizingIndices;
};

#endif // SETTINGS_H
