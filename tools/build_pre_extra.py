Import("env")

def after_upload(source, target, env):
    print("==> Uploading LittleFS image after firmware upload...")
    env.Execute("pio run --target uploadfs")

env.AddPostAction("upload", after_upload)