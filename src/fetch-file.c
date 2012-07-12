/* fetch-file.c generated by valac 0.16.1, the Vala compiler
 * generated from fetch-file.vala, do not modify */

/*
 * Copyright (C) 2010 Canonical, Ltd.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * version 3.0 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3.0 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Authors
 *      Gordon Allott <gord.allott@canonical.com>
 *      Conor Curran <conor.curran@canonical.com>
 */

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>


#define TYPE_FETCH_FILE (fetch_file_get_type ())
#define FETCH_FILE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_FETCH_FILE, FetchFile))
#define FETCH_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_FETCH_FILE, FetchFileClass))
#define IS_FETCH_FILE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_FETCH_FILE))
#define IS_FETCH_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_FETCH_FILE))
#define FETCH_FILE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_FETCH_FILE, FetchFileClass))

typedef struct _FetchFile FetchFile;
typedef struct _FetchFileClass FetchFileClass;
typedef struct _FetchFilePrivate FetchFilePrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_byte_array_free0(var) ((var == NULL) ? NULL : (var = (g_byte_array_free (var, TRUE), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
typedef struct _FetchFileFetchDataData FetchFileFetchDataData;
typedef struct _FetchFileReadSomethingAsyncData FetchFileReadSomethingAsyncData;

struct _FetchFile {
	GObject parent_instance;
	FetchFilePrivate * priv;
};

struct _FetchFileClass {
	GObjectClass parent_class;
};

struct _FetchFilePrivate {
	gchar* _uri;
	gchar* _intended_property;
	GDataInputStream* stream;
	GFile* file;
	GByteArray* data;
};

struct _FetchFileFetchDataData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	FetchFile* self;
	GFile* _tmp0_;
	GFileInputStream* _tmp1_;
	GFileInputStream* _tmp2_;
	GFileInputStream* _tmp3_;
	GDataInputStream* _tmp4_;
	GDataInputStream* _tmp5_;
	GError* e;
	GError * _inner_error_;
};

struct _FetchFileReadSomethingAsyncData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	FetchFile* self;
	gssize size;
	gssize _tmp0_;
	guint8* _tmp1_;
	guint8* buffer;
	gint buffer_length1;
	gint _buffer_size_;
	gssize bufsize;
	gboolean _tmp2_;
	gboolean _tmp3_;
	gssize _tmp4_;
	GDataInputStream* _tmp5_;
	guint8* _tmp6_;
	gint _tmp6__length1;
	gssize _tmp7_;
	gssize _tmp8_;
	gssize _tmp9_;
	gssize _tmp10_;
	gssize _tmp11_;
	gssize _tmp12_;
	guint8* _tmp13_;
	guint8* cpybuf;
	gint cpybuf_length1;
	gint _cpybuf_size_;
	guint8* _tmp14_;
	gint _tmp14__length1;
	guint8* _tmp15_;
	gint _tmp15__length1;
	gssize _tmp16_;
	GByteArray* _tmp17_;
	guint8* _tmp18_;
	gint _tmp18__length1;
	GByteArray* _tmp19_;
	guint8* _tmp20_;
	gint _tmp20__length1;
	GError* e;
	GByteArray* _tmp21_;
	const gchar* _tmp22_;
	GError * _inner_error_;
};


static gpointer fetch_file_parent_class = NULL;

GType fetch_file_get_type (void) G_GNUC_CONST;
#define FETCH_FILE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_FETCH_FILE, FetchFilePrivate))
enum  {
	FETCH_FILE_DUMMY_PROPERTY,
	FETCH_FILE_URI,
	FETCH_FILE_INTENDED_PROPERTY
};
FetchFile* fetch_file_new (const gchar* uri, const gchar* prop);
FetchFile* fetch_file_construct (GType object_type, const gchar* uri, const gchar* prop);
static void fetch_file_fetch_data_data_free (gpointer _data);
void fetch_file_fetch_data (FetchFile* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
void fetch_file_fetch_data_finish (FetchFile* self, GAsyncResult* _res_);
static gboolean fetch_file_fetch_data_co (FetchFileFetchDataData* _data_);
static void fetch_file_read_something_async (FetchFile* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
static void fetch_file_read_something_finish (FetchFile* self, GAsyncResult* _res_);
static void fetch_file_read_something_async_data_free (gpointer _data);
static gboolean fetch_file_read_something_async_co (FetchFileReadSomethingAsyncData* _data_);
static void fetch_file_read_something_async_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_);
const gchar* fetch_file_get_intended_property (FetchFile* self);
const gchar* fetch_file_get_uri (FetchFile* self);
static void fetch_file_set_uri (FetchFile* self, const gchar* value);
static void fetch_file_set_intended_property (FetchFile* self, const gchar* value);
static void g_cclosure_user_marshal_VOID__POINTER_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static GObject * fetch_file_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void fetch_file_finalize (GObject* obj);
static void _vala_fetch_file_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_fetch_file_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


FetchFile* fetch_file_construct (GType object_type, const gchar* uri, const gchar* prop) {
	FetchFile * self = NULL;
	const gchar* _tmp0_;
	const gchar* _tmp1_;
	g_return_val_if_fail (uri != NULL, NULL);
	g_return_val_if_fail (prop != NULL, NULL);
	_tmp0_ = uri;
	_tmp1_ = prop;
	self = (FetchFile*) g_object_new (object_type, "uri", _tmp0_, "intended-property", _tmp1_, NULL);
	return self;
}


FetchFile* fetch_file_new (const gchar* uri, const gchar* prop) {
	return fetch_file_construct (TYPE_FETCH_FILE, uri, prop);
}


static void fetch_file_fetch_data_data_free (gpointer _data) {
	FetchFileFetchDataData* _data_;
	_data_ = _data;
	_g_object_unref0 (_data_->self);
	g_slice_free (FetchFileFetchDataData, _data_);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void fetch_file_fetch_data (FetchFile* self, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	FetchFileFetchDataData* _data_;
	FetchFile* _tmp0_;
	_data_ = g_slice_new0 (FetchFileFetchDataData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, fetch_file_fetch_data);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, fetch_file_fetch_data_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	fetch_file_fetch_data_co (_data_);
}


void fetch_file_fetch_data_finish (FetchFile* self, GAsyncResult* _res_) {
	FetchFileFetchDataData* _data_;
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
}


static gboolean fetch_file_fetch_data_co (FetchFileFetchDataData* _data_) {
	switch (_data_->_state_) {
		case 0:
		goto _state_0;
		default:
		g_assert_not_reached ();
	}
	_state_0:
	{
		_data_->_tmp0_ = _data_->self->priv->file;
		_data_->_tmp1_ = NULL;
		_data_->_tmp1_ = g_file_read (_data_->_tmp0_, NULL, &_data_->_inner_error_);
		_data_->_tmp2_ = _data_->_tmp1_;
		if (_data_->_inner_error_ != NULL) {
			goto __catch15_g_error;
		}
		_data_->_tmp3_ = _data_->_tmp2_;
		_data_->_tmp4_ = g_data_input_stream_new ((GInputStream*) _data_->_tmp3_);
		_g_object_unref0 (_data_->self->priv->stream);
		_data_->self->priv->stream = _data_->_tmp4_;
		_g_object_unref0 (_data_->_tmp3_);
		_data_->_tmp5_ = _data_->self->priv->stream;
		g_data_input_stream_set_byte_order (_data_->_tmp5_, G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN);
	}
	goto __finally15;
	__catch15_g_error:
	{
		_data_->e = _data_->_inner_error_;
		_data_->_inner_error_ = NULL;
		g_signal_emit_by_name (_data_->self, "failed");
		_g_error_free0 (_data_->e);
	}
	__finally15:
	if (_data_->_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _data_->_inner_error_->message, g_quark_to_string (_data_->_inner_error_->domain), _data_->_inner_error_->code);
		g_clear_error (&_data_->_inner_error_);
		return FALSE;
	}
	fetch_file_read_something_async (_data_->self, NULL, NULL);
	if (_data_->_state_ == 0) {
		g_simple_async_result_complete_in_idle (_data_->_async_result);
	} else {
		g_simple_async_result_complete (_data_->_async_result);
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
}


static void fetch_file_read_something_async_data_free (gpointer _data) {
	FetchFileReadSomethingAsyncData* _data_;
	_data_ = _data;
	_g_object_unref0 (_data_->self);
	g_slice_free (FetchFileReadSomethingAsyncData, _data_);
}


static void fetch_file_read_something_async (FetchFile* self, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	FetchFileReadSomethingAsyncData* _data_;
	FetchFile* _tmp0_;
	_data_ = g_slice_new0 (FetchFileReadSomethingAsyncData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, fetch_file_read_something_async);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, fetch_file_read_something_async_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	fetch_file_read_something_async_co (_data_);
}


static void fetch_file_read_something_finish (FetchFile* self, GAsyncResult* _res_) {
	FetchFileReadSomethingAsyncData* _data_;
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
}


static void fetch_file_read_something_async_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_) {
	FetchFileReadSomethingAsyncData* _data_;
	_data_ = _user_data_;
	_data_->_source_object_ = source_object;
	_data_->_res_ = _res_;
	fetch_file_read_something_async_co (_data_);
}


static gboolean fetch_file_read_something_async_co (FetchFileReadSomethingAsyncData* _data_) {
	switch (_data_->_state_) {
		case 0:
		goto _state_0;
		case 1:
		goto _state_1;
		default:
		g_assert_not_reached ();
	}
	_state_0:
	_data_->size = (gssize) 1024;
	_data_->_tmp0_ = _data_->size;
	_data_->_tmp1_ = NULL;
	_data_->_tmp1_ = g_new0 (guint8, _data_->_tmp0_);
	_data_->buffer = _data_->_tmp1_;
	_data_->buffer_length1 = _data_->_tmp0_;
	_data_->_buffer_size_ = _data_->buffer_length1;
	_data_->bufsize = (gssize) 1;
	{
		_data_->_tmp2_ = TRUE;
		while (TRUE) {
			_data_->_tmp3_ = _data_->_tmp2_;
			if (!_data_->_tmp3_) {
				_data_->_tmp4_ = _data_->bufsize;
				if (!(_data_->_tmp4_ > ((gssize) 0))) {
					break;
				}
			}
			_data_->_tmp2_ = FALSE;
			{
				_data_->_tmp5_ = _data_->self->priv->stream;
				_data_->_tmp6_ = _data_->buffer;
				_data_->_tmp6__length1 = _data_->buffer_length1;
				_data_->_state_ = 1;
				g_input_stream_read_async ((GInputStream*) _data_->_tmp5_, _data_->_tmp6_, (gsize) _data_->_tmp6__length1, G_PRIORITY_DEFAULT, NULL, fetch_file_read_something_async_ready, _data_);
				return FALSE;
				_state_1:
				_data_->_tmp7_ = 0L;
				_data_->_tmp7_ = g_input_stream_read_finish ((GInputStream*) _data_->_tmp5_, _data_->_res_, &_data_->_inner_error_);
				_data_->_tmp8_ = _data_->_tmp7_;
				if (_data_->_inner_error_ != NULL) {
					goto __catch16_g_error;
				}
				_data_->bufsize = _data_->_tmp8_;
				_data_->_tmp9_ = _data_->bufsize;
				if (_data_->_tmp9_ < ((gssize) 1)) {
					break;
				}
				_data_->_tmp10_ = _data_->bufsize;
				_data_->_tmp11_ = _data_->size;
				if (_data_->_tmp10_ != _data_->_tmp11_) {
					_data_->_tmp12_ = _data_->bufsize;
					_data_->_tmp13_ = NULL;
					_data_->_tmp13_ = g_new0 (guint8, _data_->_tmp12_);
					_data_->cpybuf = _data_->_tmp13_;
					_data_->cpybuf_length1 = _data_->_tmp12_;
					_data_->_cpybuf_size_ = _data_->cpybuf_length1;
					_data_->_tmp14_ = _data_->cpybuf;
					_data_->_tmp14__length1 = _data_->cpybuf_length1;
					_data_->_tmp15_ = _data_->buffer;
					_data_->_tmp15__length1 = _data_->buffer_length1;
					_data_->_tmp16_ = _data_->bufsize;
					memcpy (_data_->_tmp14_, _data_->_tmp15_, (gsize) _data_->_tmp16_);
					_data_->_tmp17_ = _data_->self->priv->data;
					_data_->_tmp18_ = _data_->cpybuf;
					_data_->_tmp18__length1 = _data_->cpybuf_length1;
					g_byte_array_append (_data_->_tmp17_, _data_->_tmp18_, _data_->_tmp18__length1);
					_data_->cpybuf = (g_free (_data_->cpybuf), NULL);
				} else {
					_data_->_tmp19_ = _data_->self->priv->data;
					_data_->_tmp20_ = _data_->buffer;
					_data_->_tmp20__length1 = _data_->buffer_length1;
					g_byte_array_append (_data_->_tmp19_, _data_->_tmp20_, _data_->_tmp20__length1);
				}
			}
			goto __finally16;
			__catch16_g_error:
			{
				_data_->e = _data_->_inner_error_;
				_data_->_inner_error_ = NULL;
				g_signal_emit_by_name (_data_->self, "failed");
				_g_error_free0 (_data_->e);
			}
			__finally16:
			if (_data_->_inner_error_ != NULL) {
				_data_->buffer = (g_free (_data_->buffer), NULL);
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _data_->_inner_error_->message, g_quark_to_string (_data_->_inner_error_->domain), _data_->_inner_error_->code);
				g_clear_error (&_data_->_inner_error_);
				return FALSE;
			}
		}
	}
	_data_->_tmp21_ = _data_->self->priv->data;
	_data_->_tmp22_ = _data_->self->priv->_intended_property;
	g_signal_emit_by_name (_data_->self, "completed", _data_->_tmp21_, _data_->_tmp22_);
	_data_->buffer = (g_free (_data_->buffer), NULL);
	if (_data_->_state_ == 0) {
		g_simple_async_result_complete_in_idle (_data_->_async_result);
	} else {
		g_simple_async_result_complete (_data_->_async_result);
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
}


const gchar* fetch_file_get_uri (FetchFile* self) {
	const gchar* result;
	const gchar* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_uri;
	result = _tmp0_;
	return result;
}


static void fetch_file_set_uri (FetchFile* self, const gchar* value) {
	const gchar* _tmp0_;
	gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_uri);
	self->priv->_uri = _tmp1_;
	g_object_notify ((GObject *) self, "uri");
}


const gchar* fetch_file_get_intended_property (FetchFile* self) {
	const gchar* result;
	const gchar* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_intended_property;
	result = _tmp0_;
	return result;
}


static void fetch_file_set_intended_property (FetchFile* self, const gchar* value) {
	const gchar* _tmp0_;
	gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_intended_property);
	self->priv->_intended_property = _tmp1_;
	g_object_notify ((GObject *) self, "intended-property");
}


static void g_cclosure_user_marshal_VOID__POINTER_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__POINTER_STRING) (gpointer data1, gpointer arg_1, const char* arg_2, gpointer data2);
	register GMarshalFunc_VOID__POINTER_STRING callback;
	register GCClosure * cc;
	register gpointer data1;
	register gpointer data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 3);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__POINTER_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_pointer (param_values + 1), g_value_get_string (param_values + 2), data2);
}


static GObject * fetch_file_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	FetchFile * self;
	const gchar* _tmp0_;
	GFile* _tmp1_ = NULL;
	GByteArray* _tmp2_;
	parent_class = G_OBJECT_CLASS (fetch_file_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = FETCH_FILE (obj);
	_tmp0_ = self->priv->_uri;
	_tmp1_ = g_file_new_for_uri (_tmp0_);
	_g_object_unref0 (self->priv->file);
	self->priv->file = _tmp1_;
	_tmp2_ = g_byte_array_new ();
	_g_byte_array_free0 (self->priv->data);
	self->priv->data = _tmp2_;
	return obj;
}


static void fetch_file_class_init (FetchFileClass * klass) {
	fetch_file_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (FetchFilePrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_fetch_file_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_fetch_file_set_property;
	G_OBJECT_CLASS (klass)->constructor = fetch_file_constructor;
	G_OBJECT_CLASS (klass)->finalize = fetch_file_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), FETCH_FILE_URI, g_param_spec_string ("uri", "uri", "uri", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), FETCH_FILE_INTENDED_PROPERTY, g_param_spec_string ("intended-property", "intended-property", "intended-property", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_signal_new ("failed", TYPE_FETCH_FILE, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	g_signal_new ("completed", TYPE_FETCH_FILE, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__POINTER_STRING, G_TYPE_NONE, 2, G_TYPE_POINTER, G_TYPE_STRING);
}


static void fetch_file_instance_init (FetchFile * self) {
	self->priv = FETCH_FILE_GET_PRIVATE (self);
}


static void fetch_file_finalize (GObject* obj) {
	FetchFile * self;
	self = FETCH_FILE (obj);
	_g_free0 (self->priv->_uri);
	_g_free0 (self->priv->_intended_property);
	_g_object_unref0 (self->priv->stream);
	_g_object_unref0 (self->priv->file);
	_g_byte_array_free0 (self->priv->data);
	G_OBJECT_CLASS (fetch_file_parent_class)->finalize (obj);
}


GType fetch_file_get_type (void) {
	static volatile gsize fetch_file_type_id__volatile = 0;
	if (g_once_init_enter (&fetch_file_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (FetchFileClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) fetch_file_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (FetchFile), 0, (GInstanceInitFunc) fetch_file_instance_init, NULL };
		GType fetch_file_type_id;
		fetch_file_type_id = g_type_register_static (G_TYPE_OBJECT, "FetchFile", &g_define_type_info, 0);
		g_once_init_leave (&fetch_file_type_id__volatile, fetch_file_type_id);
	}
	return fetch_file_type_id__volatile;
}


static void _vala_fetch_file_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	FetchFile * self;
	self = FETCH_FILE (object);
	switch (property_id) {
		case FETCH_FILE_URI:
		g_value_set_string (value, fetch_file_get_uri (self));
		break;
		case FETCH_FILE_INTENDED_PROPERTY:
		g_value_set_string (value, fetch_file_get_intended_property (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_fetch_file_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	FetchFile * self;
	self = FETCH_FILE (object);
	switch (property_id) {
		case FETCH_FILE_URI:
		fetch_file_set_uri (self, g_value_get_string (value));
		break;
		case FETCH_FILE_INTENDED_PROPERTY:
		fetch_file_set_intended_property (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



