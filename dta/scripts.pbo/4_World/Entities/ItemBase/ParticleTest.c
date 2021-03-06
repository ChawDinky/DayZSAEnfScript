// Particle test for Maxman

class ParticleTest extends ItemBase
{
	protected const int	PARTICLE_PATH = ParticleList.SMOKE_GENERIC_WRECK;
	protected Particle 	m_Particle;
	
	// Constructor
	void ParticleTest()
	{
		m_Particle = Particle.PlayOnObject( PARTICLE_PATH, this, GetPosition());
	}

	// Destructor
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (m_Particle  &&  GetGame()) // GetGame() is null when the game is being shut down
		{
			m_Particle.Stop();
			GetGame().ObjectDelete(m_Particle);
		}
	}
}