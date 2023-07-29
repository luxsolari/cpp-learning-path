using System.Collections.Generic;
using SFML.Audio;

namespace OneMoreSnake.Handlers
{
    public class SoundAsset
    {
        private readonly SoundBuffer buffer = null!;
        private readonly Music sfmlMusic = null!;
        private readonly Sound sfmlSound = null!;

        public SoundAsset(string filename, bool isMusic)
        {
            if (isMusic)
            {
                sfmlMusic = new Music(filename);
                sfmlMusic.Volume = 50f;
            }
            else
            {
                buffer = new SoundBuffer(filename);
                sfmlSound = new Sound(buffer);
                sfmlSound.Volume = 60f;
            }
        }

        public void Play(bool loop = false)
        {
            if (sfmlSound == null)
            {
                sfmlMusic.Loop = loop;
                sfmlMusic.Play();
            }
            else
            {
                sfmlSound.Loop = loop;
                sfmlSound.Play();
            }
        }

        public void Stop()
        {
            if (sfmlSound == null)
                sfmlMusic.Stop();
            else
                sfmlSound.Stop();
        }

        public void Pause()
        {
            if (sfmlSound == null)
                sfmlMusic.Pause();
            else
                sfmlSound.Pause();
        }

        public SoundStatus Status()
        {
            if (sfmlSound == null)
                return sfmlMusic.Status;
            return sfmlSound.Status;
        }

        public SoundBuffer GetSoundBuffer()
        {
            return buffer;
        }

        public Sound GetSound()
        {
            if (sfmlSound != null) return sfmlSound;
            return null!;
        }

        public Music GetMusic()
        {
            if (sfmlMusic != null) return sfmlMusic;
            return null!;
        }

        public void setPitch(float pitch)
        {
            if (sfmlSound == null)
                sfmlMusic.Pitch = pitch;
            else
                sfmlSound.Pitch = pitch;
        }
    }

    public static class SoundHandler
    {
        public static Dictionary<string, SoundAsset> BGMLibrary = new Dictionary<string, SoundAsset>();
        public static Dictionary<string, SoundAsset> SFXLibrary = new Dictionary<string, SoundAsset>();

        public static void Initialize()
        {
            SFXLibrary.Add("sfx-click", new SoundAsset($"{Globals.SFXPath}/sfx-click.wav", false));
            SFXLibrary.Add("sfx-game-over", new SoundAsset($"{Globals.SFXPath}/sfx-game-over.wav", false));
            SFXLibrary.Add("sfx-pickup1", new SoundAsset($"{Globals.SFXPath}/sfx-pickup1.wav", false));
            SFXLibrary.Add("sfx-time", new SoundAsset($"{Globals.SFXPath}/sfx-time.wav", false));
            SFXLibrary.Add("sfx-wall1", new SoundAsset($"{Globals.SFXPath}/sfx-wall1.wav", false));
            SFXLibrary.Add("sfx-wall2", new SoundAsset($"{Globals.SFXPath}/sfx-wall2.wav", false));

            BGMLibrary.Add("bgm-credits", new SoundAsset($"{Globals.BGMPath}/bgm-credits.wav", true));
            BGMLibrary.Add("bgm-controls", new SoundAsset($"{Globals.BGMPath}/bgm-controls.wav", true));
            BGMLibrary.Add("bgm-gameplay1", new SoundAsset($"{Globals.BGMPath}/bgm-gameplay1.wav", true));
            BGMLibrary.Add("bgm-gameplay2", new SoundAsset($"{Globals.BGMPath}/bgm-gameplay2.wav", true));
            BGMLibrary.Add("bgm-main", new SoundAsset($"{Globals.BGMPath}/bgm-main.wav", true));
        }
    }
}