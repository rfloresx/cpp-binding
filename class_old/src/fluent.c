
#include "driver/gen/c/common/common.h"
#include "driver/gen/cpp/common/common.h"
#include "driver/gen/cpp/class/class.h"

/* Add a fluent method (setter) for each member in the corto type */
static corto_int16 cpp__fluent_visitMember(corto_walk_opt* s, corto_value *info, void *userData) {
    cpp_classWalk_t *data = userData;
    corto_type t = corto_value_typeof(info);
    corto_member m = info->is.member.t;

    corto_id id, cId;
    cpp_typeFullId(data->g, t, Cpp_Return, Cpp_ByVal, id);
    cpp_typeFullId(data->g, corto_parentof(m), Cpp_Return, Cpp_ByCRef, cId);

    /* Write implementation */
    g_fileWrite(data->header, "T& %s(%s value)",
      corto_idof(m),
      id);

    g_fileWrite(data->header, "{ ((%s)this->m_ptr)->%s = value; return this->m_this; }\n",
      cId, corto_idof(m));

    return 0;
}

static corto_int16 cpp__fluent_walkMembers(corto_type type, cpp_classWalk_t *data) {
    corto_walk_opt s;
    corto_walk_init(&s);
    s.metaprogram[CORTO_MEMBER] = cpp__fluent_visitMember;
    s.metaprogram[CORTO_BASE] = NULL;
    if (corto_metawalk(&s, type, data)) {
        goto error;
    }
    return 0;
error:
    return -1;
}

static corto_int16 cpp__fluent_create(corto_type type, cpp_classWalk_t *data) {
    corto_id classRefId, classFactoryId, returnCRef, var;

    cpp_varId(data->g, type, var);
    cpp_typeId(data->g, type, Cpp_ClassRef, classRefId);
    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);
    cpp_typeFullId(data->g, type, Cpp_Return, Cpp_ByCRef, returnCRef);

    g_fileWrite(data->header, "%s create();\n", classRefId);
    g_fileWrite(
      data->hiddenImpl,
      "%s %s::create()\n",
      classRefId,
      classFactoryId);

    g_fileWrite(data->hiddenImpl,
      "    { return %s((%s)((corto::TObjectAPI*)this)->create((corto_type)%s, &this->m_value)); }\n",
      classRefId, returnCRef, var);

    return 0;
}

static corto_int16 cpp__fluent_declare(corto_type type, cpp_classWalk_t *data) {
    corto_id classRefId, classFactoryId, returnCRef, var;

    cpp_varId(data->g, type, var);
    cpp_typeId(data->g, type, Cpp_ClassRef, classRefId);
    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);
    cpp_typeFullId(data->g, type, Cpp_Return, Cpp_ByCRef, returnCRef);

    g_fileWrite(data->header, "%s declare();\n", classRefId);
    g_fileWrite(
      data->hiddenImpl,
      "%s %s::declare()\n",
      classRefId,
      classFactoryId);

    g_fileWrite(data->hiddenImpl,
      "    { return %s((%s)((corto::TObjectAPI*)this)->declare((corto_type)%s)); }\n",
      classRefId, returnCRef, var);

    return 0;
}

static corto_int16 cpp__fluent_define(corto_type type, cpp_classWalk_t *data) {
    corto_id classFactoryId;

    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);

    g_fileWrite(data->header, "void define();\n");
    g_fileWrite(
      data->hiddenImpl,
      "void %s::define()\n", classFactoryId);

    g_fileWrite(data->hiddenImpl,
      "    { ((corto::TObjectAPI*)this)->define(&this->m_value); }\n");

    return 0;
}

static corto_int16 cpp__fluent_createChild(corto_type type, cpp_classWalk_t *data) {
    corto_id classRefId, classFactoryId, returnCRef, var;

    cpp_varId(data->g, type, var);
    cpp_typeId(data->g, type, Cpp_ClassRef, classRefId);
    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);
    cpp_typeFullId(data->g, type, Cpp_Return, Cpp_ByCRef, returnCRef);

    g_fileWrite(data->header, "%s createChild(corto::Object parent, std::string id);\n", classRefId);
    g_fileWrite(
      data->hiddenImpl,
      "%s %s::createChild(corto::Object parent, std::string id)\n",
      classRefId,
      classFactoryId);

    g_fileWrite(data->hiddenImpl,
      "    { return %s((%s)((corto::TObjectAPI*)this)->createChild(parent, id, (corto_type)%s, &this->m_value)); }\n",
      classRefId, returnCRef, var);

    return 0;
}

static corto_int16 cpp__fluent_declareChild(corto_type type, cpp_classWalk_t *data) {
    corto_id classRefId, classFactoryId, returnCRef, var;

    cpp_varId(data->g, type, var);
    cpp_typeId(data->g, type, Cpp_ClassRef, classRefId);
    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);
    cpp_typeFullId(data->g, type, Cpp_Return, Cpp_ByCRef, returnCRef);

    g_fileWrite(
      data->header,
      "%s declareChild(corto::Object parent, std::string id);\n",
      classRefId);

    g_fileWrite(
      data->hiddenImpl,
      "%s %s::declareChild(corto::Object parent, std::string id)\n",
      classRefId,
      classFactoryId);

    g_fileWrite(data->hiddenImpl,
      "    { return %s((%s)((corto::TObjectAPI*)this)->declareChild(parent, id, (corto_type)%s)); }\n",
      classRefId, returnCRef, var);

    return 0;
}


static corto_int16 cpp__fluent_value(corto_type type, cpp_classWalk_t *data) {
    corto_id classValId, classFactoryId, var;

    cpp_varId(data->g, type, var);
    cpp_typeId(data->g, type, Cpp_ClassVal, classValId);
    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);

    g_fileWrite(data->header, "%s value();\n", classValId);
    g_fileWrite(data->hiddenImpl, "%s %s::value()\n", classValId, classFactoryId);
    g_fileWrite(data->hiddenImpl, "    { return %s(&this->m_value); }\n", classValId);

    return 0;
}

static corto_int16 cpp__fluent_update(corto_type type, cpp_classWalk_t *data) {
    corto_id classFactoryId;

    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);

    g_fileWrite(data->header, "void update();\n");
    g_fileWrite(data->hiddenImpl, "void %s::update()\n", classFactoryId);
    g_fileWrite(data->hiddenImpl,
      "    { ((corto::TObjectAPI*)this)->update(&this->m_value); }\n");

    return 0;
}

corto_int16 cpp__fluentTemplDecl(corto_type type, cpp_classWalk_t *data) {
    corto_id baseTemplateFactoryId, templateFactoryId, classFactory;
    corto_interface interface = corto_interface(type);

    if (!interface->base) {
        strcpy(baseTemplateFactoryId, "::corto::TObject");
    } else {
        cpp_typeFullId(data->g, interface->base, Cpp_TemplateFactory, Cpp_ById, baseTemplateFactoryId);
    }

    cpp_typeId(data->g, type, Cpp_TemplateFactory, templateFactoryId);
    cpp_typeId(data->g, type, Cpp_ClassFactory, classFactory);

    g_fileWrite(data->header, "// Template with fluent methods returning T=%s for corto type %s\n", classFactory, corto_fullpath(NULL, type));
    g_fileWrite(data->header, "// By parameterizing T, fluent subclasses can reuse this code.\n");
    g_fileWrite(data->header, "template <class T>\n");
    g_fileWrite(data->header, "class %s : public %s<T>\n", templateFactoryId, baseTemplateFactoryId);
    g_fileWrite(data->header, "{\n");
    g_fileWrite(data->header, "public:\n");
    g_fileIndent(data->header);
    g_fileWrite(data->header, "%s(T& _this, void *ptr) : %s<T>(_this, ptr) { }\n", templateFactoryId, baseTemplateFactoryId);
    g_fileWrite(data->header, "%s(T& _this, corto_object ref, void *ptr) : %s<T>(_this, ref, ptr) { }\n", templateFactoryId, baseTemplateFactoryId);

    if (corto_instanceof(corto_interface_o, type) && corto_interface(type)->base) {
        g_fileWrite(data->header, "%s<T> super() ", baseTemplateFactoryId);
        g_fileWrite(data->header, "{ return %s<T>(this->m_this, this->ptr); }\n", baseTemplateFactoryId);
    }

    if (cpp__fluent_walkMembers(type, data)) {
        goto error;
    }

    g_fileDedent(data->header);
    g_fileWrite(data->header, "};\n");
    g_fileWrite(data->header, "\n");

    return 0;
error:
    return -1;
}

corto_int16 cpp__fluentDecl(corto_type type, cpp_classWalk_t *data) {
    corto_id cId, var, class, classFactory, classFactoryId, templateFactory;

    cpp_typeId(data->g, type, Cpp_Class, class);
    cpp_typeId(data->g, type, Cpp_ClassFactory, classFactory);
    cpp_typeId(data->g, type, Cpp_TemplateFactory, templateFactory);
    cpp_typeFullId(data->g, type, Cpp_ClassFactory, Cpp_ById, classFactoryId);
    cpp_typeFullId(data->g, type, Cpp_Return, Cpp_ByCVal, cId);
    cpp_varId(data->g, type, var);

    g_fileWrite(data->header, "\n");

    if (cpp__fluentTemplDecl(type, data)) {
        goto error;
    }

    g_fileWrite(data->header, "// Fluent factory class for corto type %s\n", corto_fullpath(NULL, type));
    g_fileWrite(data->header, "class %s : public %s<%s>\n",
      classFactory, templateFactory, classFactory);
    g_fileWrite(data->header, "{\n");
    g_fileWrite(data->header, "public:\n");
    g_fileIndent(data->header);

    g_fileWrite(data->header, "%s();\n", classFactory);
    g_fileWrite(data->hiddenImpl,
      "%s::%s() : %s<%s>(*this, &m_value) { m_type = (corto_type)%s; memset(&m_value, 0, sizeof(m_value)); corto_ptr_init(&m_value, %s);}\n",
      classFactoryId, classFactory, templateFactory, classFactory, var, var);

    g_fileWrite(data->header, "%s(%s& obj);\n", classFactory, class);
    g_fileWrite(data->hiddenImpl,
      "%s::%s(%s& obj) : %s<%s>(*this, &m_value) { m_type = (corto_type)%s; memset(&m_value, 0, sizeof(m_value)); corto_ptr_init(&m_value, %s);}\n",
      classFactoryId, classFactory, class, templateFactory, classFactory, var, var);

    g_fileWrite(data->header, "%s(%s& obj, corto_object ref);\n", classFactory, class);
    g_fileWrite(data->hiddenImpl,
      "%s::%s(%s& obj, corto_object ref) : %s<%s>(*this, ref, &m_value) { m_type = (corto_type)%s; memset(&m_value, 0, sizeof(m_value)); corto_ptr_init(&m_value, %s);}\n",
      classFactoryId, classFactory, class, templateFactory, classFactory, var, var);

    g_fileWrite(data->header, "\n");

    if (cpp__fluent_declare(type, data)) {
        goto error;
    }
    if (cpp__fluent_create(type, data)) {
        goto error;
    }
    if (cpp__fluent_declareChild(type, data)) {
        goto error;
    }
    if (cpp__fluent_createChild(type, data)) {
        goto error;
    }
    if (cpp__fluent_define(type, data)) {
        goto error;
    }
    if (cpp__fluent_update(type, data)) {
        goto error;
    }
    if (cpp__fluent_value(type, data)) {
        goto error;
    }

    g_fileDedent(data->header);
    g_fileWrite(data->header, "private:\n");
    g_fileIndent(data->header);
    g_fileWrite(data->header, "struct %s m_value;\n", cId);
    g_fileDedent(data->header);
    g_fileWrite(data->header, "};\n");

    return 0;
error:
    return -1;
}
