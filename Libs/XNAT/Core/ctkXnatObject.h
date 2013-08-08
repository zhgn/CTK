/*=============================================================================

  Plugin: org.commontk.xnat

  Copyright (c) University College London,
    Centre for Medical Image Computing

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#ifndef ctkXnatObject_h
#define ctkXnatObject_h

#include "ctkXNATCoreExport.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QMetaType>

class ctkXnatConnection;
class ctkXnatObjectPrivate;

class CTK_XNAT_CORE_EXPORT ctkXnatObject
{

public:

  typedef QSharedPointer<ctkXnatObject> Pointer;
  typedef QWeakPointer<ctkXnatObject> WeakPointer;

  virtual ~ctkXnatObject();

  QString id() const;
  QString uri() const;
  QString name() const;
  QString description() const;

  QString property(const QString& name) const;
  void setProperty(const QString& name, const QVariant& value);

  QList<QString> properties();
  
  ctkXnatObject::Pointer parent() const;
  QList<ctkXnatObject::Pointer> children() const;

  void addChild(Pointer& child);
  void removeChild(Pointer& child);

  bool isFetched() const;

  virtual void reset();
  void fetch();

  virtual void download(const QString&);
  virtual void upload(const QString&);
  virtual void add(const QString&);
  virtual void remove();

  virtual bool isFile() const;
  virtual bool receivesFiles() const;
  virtual bool holdsFiles() const;
  virtual bool isDeletable() const;
  virtual bool isModifiable() const;

  
protected:

  ctkXnatObject();
  ctkXnatObject(ctkXnatObjectPrivate& dd);

  virtual ctkXnatConnection* connection() const;

  void setId(const QString& id);
  void setUri(const QString& uri);
  void setName(const QString& name);
  void setDescription(const QString& description);

  const QScopedPointer<ctkXnatObjectPrivate> d_ptr;

private:

  friend class ctkXnatConnection;

  virtual void fetchImpl() = 0;

  Q_DECLARE_PRIVATE(ctkXnatObject)
  Q_DISABLE_COPY(ctkXnatObject)
};

Q_DECLARE_METATYPE(ctkXnatObject::Pointer)

#endif